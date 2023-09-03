#include "MyEnvironment.hpp"

#include <gtest/gtest.h>

#include <ranges>
#include <numeric>

#include "DSABufferStatic.hpp"


TEST(F, f){
    DSABufferStatic<BufferType::Array, BufferStorageUsage::MapReadBit> bufferStatic;
    ASSERT_TRUE(glIsBuffer(bufferStatic) == GL_TRUE);
    std::vector<GLint> CPUvec(1000);
    std::iota(CPUvec.begin(), CPUvec.end(), 0);
    bufferStatic.storage(CPUvec);
    std::vector<GLint> GPUvec = bufferStatic;

    ASSERT_TRUE(std::ranges::equal(CPUvec, GPUvec));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new MyEnvironment);
    return RUN_ALL_TESTS();
}
