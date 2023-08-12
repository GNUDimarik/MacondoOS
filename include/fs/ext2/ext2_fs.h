/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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

#ifndef MACONDOOS_INCLUDE_FS_EXT2_EXT2_FS_H
#define MACONDOOS_INCLUDE_FS_EXT2_EXT2_FS_H

#include <asm/types.h>

/* ext2 super block magic number */
#define EXT2_SUPER_MAGIC 0xEF53

#define EXT2_OFFSET_SUPER 1024

/* fs state */
#define EXT2_VALID_FS 1 /* Unmounted cleanly */
#define EXT2_ERROR_FS 2 /* Errors detected */

/* errors */
#define EXT2_ERRORS_CONTINUE 1 /* continue as if nothing happened */
#define EXT2_ERRORS_RO       2 /* remount read-only */
#define EXT2_ERRORS_PANIC    3 /* cause a kernel panic */

/* creator */
#define EXT2_OS_LINUX   0
#define EXT2_OS_HURD    1
#define EXT2_OS_MASIX   2
#define EXT2_OS_FREEBSD 3
#define EXT2_OS_LITES   4

/* revision */
#define EXT2_GOOD_OLD_REV 0
#define EXT2_DYNAMIC_REV  1

/* refuid */
#define EXT2_DEF_RESUID 0

/* refgid */
#define EXT2_DEF_RESGID 0

/* first usable inode number for EXT2_GOOD_OLD_REV */
#define EXT2_GOOD_OLD_FIRST_INO             11

/* inode size for EXT2_GOOD_OLD_REV */
#define EXT2_GOOD_OLD_INODE_SIZE            128

/* bitmask of compatible features */

/* Block pre-allocation for new directories */
#define EXT2_FEATURE_COMPAT_DIR_PREALLOC    0x0001
#define EXT2_FEATURE_COMPAT_IMAGIC_INODES   0x0002
#define EXT3_FEATURE_COMPAT_HAS_JOURNAL     0x0004 /* An Ext3 journal exists */
#define EXT2_FEATURE_COMPAT_EXT_ATTR        0x0008 /* Extended inode attributes are present */
#define EXT2_FEATURE_COMPAT_RESIZE_INO      0x0010 /* Non-standard inode size used */
#define EXT2_FEATURE_COMPAT_DIR_INDEX       0x0020 /* Directory indexing (HTree) */

/* Incompatible features */

/* Disk/File compression is used */
#define EXT2_FEATURE_INCOMPAT_COMPRESSION   0x0001
#define EXT2_FEATURE_INCOMPAT_FILETYPE      0x0002
#define EXT3_FEATURE_INCOMPAT_RECOVER       0x0004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV   0x0008
#define EXT2_FEATURE_INCOMPAT_META_BG       0x0010

/* Read only features */

#define EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER 0x0001 /* Sparse Superblock */
#define EXT2_FEATURE_RO_COMPAT_LARGE_FILE   0x0002 /* Large file support, 64-bit file size */
#define EXT2_FEATURE_RO_COMPAT_BTREE_DIR    0x0004 /* Binary tree sorted directory files */

#define EXT2_LABEL_LEN                        16     /* Formatted volume name len */

/* Ext2 compression algorithm */
#define EXT2_LZV1_ALG                       0x00000001
#define EXT2_LZRW3A_ALG                     0x00000002
#define EXT2_GZIP_ALG                       0x00000004
#define EXT2_BZIP2_ALG                      0x00000008
#define EXT2_LZO_ALG                        0x00000010

/* TODO: write a comments */
struct ext2_super_block
{
    __le32 s_inodes_count;      /* Total number of inodes in file system */
    __le32 s_blocks_count;      /* Total number of blocks in file system */
    __le32 s_r_blocks_count;    /* Number of blocks reserved for superuser */
    __le32 s_free_blocks_count; /* Total number of unallocated blocks */
    __le32 s_free_inodes_count; /* Total number of unallocated inodes */
    __le32 s_first_data_block;  /* Block number of the block containing the superblock  */
    __le32u s_log_block_size;    /*  1024 << s_log_block_size */
    __le32
        s_log_frag_size;      /* (1024 << s_log_frag_size) : (1024 >> -s_log_frag_size) or 0  if s_log_frag_size is negative */
    __le32 s_blocks_per_group;  /* Number of blocks in each block group */
    __le32 s_frags_per_group;   /* Number of fragments in each block group */
    __le32 s_inodes_per_group;  /* Number of inodes in each block group */
    __le32 s_mtime;          /* Last mount time */
    __le32 s_wtime;          /* Last write to fs time */
    __le16
        s_mnt_count;         /* Number of times the volume has been mounted since its last consistency check (fsck) */
    __le16 s_max_mnt_count;     /* Number of mounts allowed before a consistency check */
    __le16u s_magic;             /* Magic number */
    __le16 s_state;             /* Fs state (clean/errors) */
    __le16 s_minor_rev_level;   /* Minor revision level */
    __le32 s_lastcheck;      /* Time of the last check */
    __le32 s_checkinterval;  /* Max interval between check */
    __le32 s_creator_os;        /* Creator OS */
    __le32 s_rev_level;         /* Revision level (0/1) */
    __le16 s_def_resuid;        /* User ID that can use reserved blocks */
    __le16 s_def_resgid;        /* Group ID that can use reserved blocksGroup ID that can use reserved blocks0 */
    /* -- EXT2_DYNAMIC_REV Specific -- */
    __le32 s_first_ino;
    __le16 s_inode_size;
    __le16 s_block_group_nr;
    __le32 s_feature_compat;
    __le32 s_feature_incompat;
    __le32 s_feature_ro_compat;
    char s_uuid[16];
    char s_volume_name[16];
    __le8 s_last_mounted[64];
    __le32 s_algo_bitmap;
    /* -- Performance Hints -- */
    __le8 s_prealloc_blocks;
    __le8 s_prealloc_dir_blocks;
    __le16 s_pad; /* alignment */
    /* -- Journaling Support -- */
    __le8 s_journal_uuid[16];
    __le32 s_journal_inum;
    __le32 s_journal_dev;
    __le32 s_last_orphan;
    /* -- Directory Indexing Support -- */
    __le32 s_hash_seed[4];
    __le8 s_def_hash_version;
    __le8 s_reserved[3];
    /* -- Other options -- */
    __le32 s_default_mount_options;
    __le32 s_first_meta_bg;
    __le8 s_unused[760];
};

struct ext2_group_desc
{
    __le32 bg_block_bitmap;        /* Block address of block usage bitmap */
    __le32 bg_inode_bitmap;        /* Block address of inode usage bitmap  */
    __le32 bg_inode_table;         /* Starting block address of inode table */
    __le16 bg_free_blocks_count;   /* Number of unallocated blocks in group */
    __le16 bg_free_inodes_count;   /* Number of unallocated inodes in group */
    __le16 bg_used_dirs_count;     /* Number of directories in group */
    __le16 bg_pad;
    __le32 bg_reserved[3];
};

struct ext2_inode
{
    __le16u i_mode;
    __le16u i_uid;
    __le32u i_size;
    __le32u i_atime;
    __le32u i_ctime;
    __le32u i_mtime;
    __le32u i_dtime;
    __le16u i_gid;
    __le16u i_links_count;
    __le32u i_blocks;
    __le32u i_flags;
    __le32u i_reserved1;
    __le32u i_block[15];
    __le32u i_version;
    __le32u i_file_acl;
    __le32u i_dir_acl;
    __le16u i_faddr;
    __le8u i_frag;
    __le8u i_fsize;
    __le32u i_reserved2[3];
};
struct ext2_dir_entry
{
    struct ext2_inode *inode;
    __le16 name_len;
    __le16 type;
    char name[255];
};

#endif //MACONDOOS_INCLUDE_FS_EXT2_EXT2_FS_H