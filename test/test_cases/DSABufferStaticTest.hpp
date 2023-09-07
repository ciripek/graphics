#pragma once

#include <gtest/gtest.h>

#include <numeric>
#include <ranges>

#include "DSABufferStatic.hpp"

TEST(DSABufferStatic, storage) {
  DSABufferStatic<BufferType::Array, BufferStorageUsage::MapReadBit>
      bufferStatic;

  ASSERT_TRUE(glIsBuffer(bufferStatic) == GL_TRUE);

  std::vector<GLint> CPUvec(1000);
  std::iota(CPUvec.begin(), CPUvec.end(), 0);

  bufferStatic.storage(CPUvec);
  std::vector<GLint> GPUvec = bufferStatic;

  ASSERT_TRUE(std::ranges::equal(CPUvec, GPUvec));
}

TEST(DSABufferStatic, subdata) {
  DSABufferStatic<BufferType::Array, BufferStorageUsage::MapReadBit |
                                         BufferStorageUsage::DynamicStorageBit>
      bufferStatic;

  std::vector<GLint> CPUvec(1000);
  std::iota(CPUvec.begin(), CPUvec.end(), 0);

  bufferStatic.storage(CPUvec);
  std::vector<GLint> GPUvec = bufferStatic;

  ASSERT_TRUE(std::ranges::equal(CPUvec, GPUvec));

  std::vector<GLint> CPUvec2(1000);
  std::iota(CPUvec2.begin(), CPUvec2.end(), 1000);

  bufferStatic.subData(CPUvec2);
  std::vector<GLint> GPU2vec = bufferStatic;
  ASSERT_TRUE(std::ranges::equal(CPUvec2, GPU2vec));
}