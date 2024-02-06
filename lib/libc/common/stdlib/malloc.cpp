/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stddef.h>
#include <errno.h>
#include <string.h>

__BEGIN_DECLS

#define LOG_TAG "Malloc"

#include <linux_debug.h>

/*
 * actually word should be address size but in terms of asm it's even qword.
 */
#define WSIZE __SIZEOF_POINTER__
/* block header size */
#define HEADER_SIZE WSIZE
/* free block header size */
#define FOOTER_SIZE HEADER_SIZE
/* size of header and footer e.g. overhead */
#define OVERHEAD_SIZE HEADER_SIZE + FOOTER_SIZE

static void *sMemHeapStart = nullptr;
static void *sMemHeapEnd = nullptr;

#define SIZE_T_PTR(ptr) (reinterpret_cast<size_t*>(ptr))
#define CHAR_PTR(ptr) (reinterpret_cast<char*>(ptr))
#define USER_PTR(ptr) (CHAR_PTR(ptr) + HEADER_SIZE)

#define ALLOCATED   1 /* block is allocated */
#define UNALLOCATED 0 /* block is free */

/*
 * Put size and allocation state to implicit header
 */

static inline void mem_pack(void *p, size_t size, size_t flags)
{
    *SIZE_T_PTR(p) = size | flags;
}

/*
 * In our logic user land pointer is address next after implicit header
 */

static inline void *mem_header(void *ptr)
{
    return CHAR_PTR(ptr) - HEADER_SIZE;
}

static inline size_t mem_block_size(void *p)
{
    return (*SIZE_T_PTR(mem_header(p)) & ~0x01);
}

static inline size_t mem_block_size_with_overhead(void *ptr)
{
    return mem_block_size(ptr) + OVERHEAD_SIZE;
}

static inline void *mem_footer(void *ptr)
{
    return CHAR_PTR(ptr) + mem_block_size(ptr) - FOOTER_SIZE;
}

static inline void mem_put_to_header(void *ptr, size_t size,
                                     size_t flags)
{
    void *p = mem_header(ptr);
    mem_pack(p, size, flags);
}

static inline void mem_put_to_footer(void *ptr, size_t size,
                                     size_t flags)
{
    void *p = mem_footer(ptr);
    mem_pack(p, size, flags);
}

static inline void *mem_init_block(void *ptr, size_t size,
                                   size_t flags)
{
    mem_put_to_header(ptr, size, flags);
    mem_put_to_footer(ptr, size, flags);
    return ptr;
}

static inline bool mem_block_allocated(void *p)
{
    return (*SIZE_T_PTR(mem_header(p)) & 0x01) == ALLOCATED;
}

static inline void *mem_next_block(void *ptr)
{
    return CHAR_PTR(mem_header(ptr)) + mem_block_size(ptr) + OVERHEAD_SIZE;
}

static inline void *mem_prev_block(void *ptr)
{
    char *header = CHAR_PTR(mem_header(ptr));
    //char* prev_blk_footer = CHAR_PTR(header) - FOOTER_SIZE;
    return (header - mem_block_size(header));
}

static void *mem_place(void *block, size_t size)
{
    size_t cur_size = mem_block_size(block);
    size -= OVERHEAD_SIZE;

    if (size < cur_size) {
        size_t new_size = cur_size - size - HEADER_SIZE;
        mem_put_to_footer(block, new_size, UNALLOCATED);
        mem_put_to_header(block, size, ALLOCATED);
        mem_put_to_footer(block, size, ALLOCATED);
        mem_put_to_header(mem_next_block(block), new_size, UNALLOCATED);
        return block;
    }
    else if (size == cur_size) {
        mem_put_to_header(block, size, ALLOCATED);
        mem_put_to_footer(block, size, ALLOCATED);
        return block;
    }
    else {
        ALOGD("%s(): cur_size is %lu size is %lu. Ignore request\n",
              __func__, cur_size, size);
    }

    return NULL;
}

static void *mem_find_first_fit(size_t size)
{
    for (void *cur_blk = sMemHeapStart; cur_blk < sMemHeapEnd; cur_blk = mem_next_block(cur_blk)) {
        if (!mem_block_allocated(cur_blk) && mem_block_size(cur_blk) >= size) {
            return cur_blk;
        }
    }

    return NULL;
}

static void *mem_merge(void *ptr)
{
    bool next_allocated = mem_block_allocated(mem_next_block(ptr));
    bool prev_allocated = mem_block_allocated(mem_prev_block(ptr));
    size_t size = mem_block_size(ptr);

    if (prev_allocated && next_allocated) {
        /* Do nothing */
    }

    else if (prev_allocated && !next_allocated) {
        size += mem_block_size(mem_next_block(ptr)) + FOOTER_SIZE;
        void *footer = mem_footer(ptr);
        mem_put_to_header(ptr, size, UNALLOCATED);
        mem_pack(footer, size, UNALLOCATED);
    }

    else if (!prev_allocated && next_allocated) {
        void *prev = mem_prev_block(ptr);
        void *footer = mem_footer(ptr);
        size += mem_block_size(prev) + FOOTER_SIZE;
        mem_put_to_header(prev, size, UNALLOCATED);
        mem_pack(footer, size, UNALLOCATED);
    }

    else if (!prev_allocated && !next_allocated) {
        void *header = mem_header(mem_prev_block(ptr));
        void *footer = mem_footer(mem_next_block(ptr));
        size += mem_block_size(mem_prev_block(ptr)) +
            mem_block_size(mem_next_block(ptr)) + OVERHEAD_SIZE;
        mem_pack(header, size, UNALLOCATED);
        mem_pack(footer, size, UNALLOCATED);
    }

    return ptr;
}

/**
 * @brief malloc - allocates unused space for an object whose size in bytes is
 *                 specified by size and whose value is unspecified.
 * @param size   - desired size of block for allocation
 * @return         Upon successful completion with size not equal to 0, malloc()
 *                 shall return a pointer to the allocated space. If size is 0,
 *                 either:
 *
 * A null pointer shall be returned and errno set to 0
 * Otherwise, it shall return a null pointer and set errno to ENOMEM
 */
void *mem_malloc(size_t size)
{
    size_t asize = 0;
    void *bp = NULL;

    if (size < WSIZE) {
        asize = WSIZE + OVERHEAD_SIZE;
    }
    else {
        asize = WSIZE * ((size + OVERHEAD_SIZE + WSIZE - 1) / WSIZE);
    }

    bp = mem_find_first_fit(asize);

    if (bp != NULL) {
        bp = mem_place(bp, asize);
    }

    return bp;
}

/**
 * @brief free - deallocate previously allocated via alloc() memory
 * @param ptr  - pointer to previously allocated block
 *
 * if the argument does not match a pointer earlier returned by a function
 * in POSIX.1-2017 that allocates memory as if by malloc(), or if the space has
 * been deallocated by a call to free() or realloc(), the behavior is undefined.
 *
 * Any use of a pointer that refers to freed space results in undefined behavior.
 */
void mem_free(void *ptr)
{
    if (ptr != NULL && mem_block_allocated(ptr)) {
        size_t size = mem_block_size(ptr);
        mem_init_block(ptr, size, UNALLOCATED);
        mem_merge(ptr);
    }
    else {
        ALOGE("%s(): Invalid pointer\n", __func__);
    }
}

/**
 * @brief realloc - deallocates the old object pointed to by ptr and return
 *                  a pointer to a new object that has the size specified by size.
 * @param ptr     - pointer to previously allocated via malloc() block
 * @param size    - new desired size of newly allocated block
 * @return        - newly allocated block with the same content or NULL
 *                  In case of error errno is set to ENOMEM
 *
 * The contents of the new object is the same as that of the old object prior
 * to deallocation, up to the lesser of the new and old sizes.
 * Any bytes in the new object beyond the size of the old object have
 * indeterminate values. If the size of the space requested is zero, then
 * returns the same pointer
 */
void *mem_realloc(void *ptr, size_t size)
{
    if (size == 0 || ptr == nullptr) {
        return ptr;
    }

    if (ptr != NULL && mem_block_allocated(ptr)) {
        size_t asize = WSIZE * ((size + OVERHEAD_SIZE + WSIZE - 1) / WSIZE);
        size_t cur_size = mem_block_size(ptr);

        if (asize > cur_size) {
            void *blk = mem_find_first_fit(asize);

            if (blk != nullptr) {
                mem_place(blk, asize);
                memmove(blk, ptr, mem_block_size(ptr));
                mem_free(ptr);
                return blk;
            }
        }
        else if (asize < cur_size) {
            void *p = mem_place(ptr, asize);
            mem_merge(mem_next_block(ptr));
            return p;
        }
    }
    else {
        ALOGD("%s(): Invalid pointer\n", __func__);
        return NULL;
    }

    return ptr;
}

/**
 * @brief calloc - allocates unused space for an array of count elements each of
 *                 whose size in bytes is size. Each byte of allocated memory is
 *                 set to 0
 * @param count  - count of an array elements
 * @param size   - size of one element of the array
 * @return       - allocated memory or NULL pointer. In case of error
 *                 errno is set to ENOMEM
 */
void *mem_calloc(size_t count, size_t size)
{
    void *p = mem_malloc(count * size);

    if (p != nullptr) {
        memset(p, 0, size);
    }

    return p;
}

int mem_init(void *start, size_t sizeInBytes)
{
    if (start != nullptr && sizeInBytes > 0) {
        /* first and last blocks must be always allocated */
        sMemHeapStart = start;
        mem_init_block(USER_PTR(sMemHeapStart), WSIZE, ALLOCATED);
        sMemHeapEnd = CHAR_PTR(start) + sizeInBytes - (OVERHEAD_SIZE + WSIZE);
        mem_init_block(USER_PTR(sMemHeapEnd), WSIZE, ALLOCATED);
        void *heap = mem_next_block(USER_PTR(sMemHeapStart));
        /* take in account reserved blocks and their overheads including heap
         * sMemHeapStart has overhead 16 bytes and size 8 bytes
         * the same about sMemHeapEnd
         */
        size_t reserved_size = (OVERHEAD_SIZE + WSIZE) * 2;
        size_t heap_size = sizeInBytes - reserved_size;
        mem_init_block(heap, heap_size, UNALLOCATED);
        return 0;
    }

    return EINVAL;
}

void mem_dump()
{
    void *cur_blk = nullptr;
    size_t total_memory = 0;
    size_t total_with_overhead = 0;
    size_t total_blocks = 0;

    ALOGD(
        "*************************MEMORY DUMP*************************");

    if (sMemHeapStart != nullptr && sMemHeapEnd != nullptr) {
        for (cur_blk = USER_PTR(sMemHeapStart); cur_blk <= USER_PTR(sMemHeapEnd); total_blocks++) {
            size_t blk_size = mem_block_size(cur_blk);
            size_t blk_size_with_overhead = mem_block_size_with_overhead(cur_blk);
            total_memory += blk_size;
            total_with_overhead += blk_size_with_overhead;
            const char *format = cur_blk == sMemHeapStart || cur_blk == sMemHeapEnd
                                 ? "service block address %p size %12lu \t size with overhead %8lu state %s"
                                 : "block address         %p size %12lu \t size with overhead %8lu state %s";

            ALOGD(format, cur_blk,
                  blk_size, blk_size_with_overhead,
                  mem_block_allocated(cur_blk) == ALLOCATED ? "allocated" : "free");
            cur_blk = mem_next_block(cur_blk);
        }
    }
    else {
        ALOGD("Not initialized");
    }

    ALOGD(
        "**********************END OF MEMORY DUMP**********************");

    ALOGD("total memory               %12lu bytes", total_memory);
    ALOGD("total memory with overhead %12lu bytes", total_with_overhead);
    ALOGD("total total_blocks count   %12lu", total_blocks);
}

__END_DECLS