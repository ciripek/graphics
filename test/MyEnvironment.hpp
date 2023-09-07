#pragma once

#include <gtest/gtest.h>

#include <SDL.h>

class MyEnvironment final : public testing::Environment {
 public:
  MyEnvironment() = default;
  ~MyEnvironment() override = default;

  // Override this to define how to set up the environment.
  void SetUp() override;

  // Override this to define how to tear down the environment.
  void TearDown() override;

 private:
  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
};
