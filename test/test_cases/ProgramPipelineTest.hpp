#pragma once

#include <gtest/gtest.h>

#include <GL/glew.h>

#include "ProgramPipeline.hpp"

class ProgramPipelineTest : public ::testing::Test {
 protected:
  ProgramPipeline programPipeline;
};

TEST_F(ProgramPipelineTest, constructor) {
  EXPECT_TRUE(glIsProgramPipeline(programPipeline) == GL_TRUE);
}