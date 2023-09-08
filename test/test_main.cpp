#include "MyEnvironment.hpp"

#include <gtest/gtest.h>

#include "DSABufferStaticTest.hpp"
#include "ProgramPipelineTest.hpp"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::AddGlobalTestEnvironment(new MyEnvironment());
  return RUN_ALL_TESTS();
}
