//===-- Unittests for memmove ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/string.h"
#include <vector>

TEST(LlvmLibcMemmoveTest, MoveZeroByte) {
  char Buffer[] = {'a', 'b', 'y', 'z'};
  const char Expected[] = {'a', 'b', 'y', 'z'};
  void *const Dst = Buffer;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer + 2, 0);
  EXPECT_EQ(Ret, Dst);
  EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

TEST(LlvmLibcMemmoveTest, DstAndSrcPointToSameAddress) {
  char Buffer[] = {'a', 'b'};
  const char Expected[] = {'a', 'b'};
  void *const Dst = Buffer;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer, 1);
  EXPECT_EQ(Ret, Dst);
    EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

TEST(LlvmLibcMemmoveTest, DstStartsBeforeSrc) {
  // Set boundary at beginning and end for not overstepping when
  // copy forward or backward.
  char Buffer[] = {'z', 'a', 'b', 'c', 'z'};
  const char Expected[] = {'z', 'b', 'c', 'c', 'z'};
  void *const Dst = Buffer + 1;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer + 2, 2);
  EXPECT_EQ(Ret, Dst);
  EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

TEST(LlvmLibcMemmoveTest, DstStartsAfterSrc) {
  char Buffer[] = {'z', 'a', 'b', 'c', 'z'};
  const char Expected[] = {'z', 'a', 'a', 'b', 'z'};
  void *const Dst = Buffer + 2;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer + 1, 2);
  EXPECT_EQ(Ret, Dst);
  EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

// e.g. `Dst` follow `src`.
// str: [abcdefghij]
//      [__src_____]
//      [_____Dst__]
TEST(LlvmLibcMemmoveTest, SrcFollowDst) {
  char Buffer[] = {'z', 'a', 'b', 'z'};
  const char Expected[] = {'z', 'b', 'b', 'z'};
  void *const Dst = Buffer + 1;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer + 2, 1);
  EXPECT_EQ(Ret, Dst);
  EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

TEST(LlvmLibcMemmoveTest, DstFollowSrc) {
  char Buffer[] = {'z', 'a', 'b', 'z'};
  const char Expected[] = {'z', 'a', 'a', 'z'};
  void *const Dst = Buffer + 2;
  void *const Ret = __STD_NAMESPACE::memmove(Dst, Buffer + 1, 1);
  EXPECT_EQ(Ret, Dst);
  EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer, Expected, ARRAY_SIZE(Buffer)), 0);
}

static constexpr int kMaxSize = 512;

char GetRandomChar() {
  static constexpr const uint64_t A = 1103515245;
  static constexpr const uint64_t C = 12345;
  static constexpr const uint64_t M = 1ULL << 31;
  static uint64_t Seed = 123456789;
  Seed = (A * Seed + C) % M;
  return Seed;
}

void Randomize(std::vector<char> Buffer) {
  for (auto &current : Buffer)
    current = GetRandomChar();
}

TEST(LlvmLibcMemmoveTest, Thorough) {
  using LargeBuffer = std::vector<char>;
  LargeBuffer GroundTruth;
  GroundTruth.resize(3 * kMaxSize);
  Randomize(GroundTruth);
  for (int Size = 0; Size < kMaxSize; ++Size) {
    for (int Offset = -Size; Offset < Size; ++Offset) {
      LargeBuffer Buffer = GroundTruth;
      LargeBuffer Expected = GroundTruth;
      size_t DstOffset = kMaxSize;
      size_t SrcOffset = kMaxSize + Offset;
      for (int I = 0; I < Size; ++I)
        Expected[DstOffset + I] = GroundTruth[SrcOffset + I];
      void *const Dst = Buffer.data() + DstOffset;
      void *const Ret =
          __STD_NAMESPACE::memmove(Dst, Buffer.data() + SrcOffset, Size);
      EXPECT_EQ(Ret, Dst);
      EXPECT_EQ(__STD_NAMESPACE::memcmp(Buffer.data(), Expected.data(), Buffer.size()), 0);
    }
  }
}