#pragma once

#include <sstream>

#include "Application.h"
#include "game/SimpleEntity.h"

class Game : public Application {
 public:
  Game(int argc, char* argv[], const char* title = "Application",
       int width = 1280, int height = 720,
       bool lock_framerate_to_screen = false, int target_fps = 60);
  ~Game();
  void run();

 private:
  void update();
  void draw();
  void parseArgs(int argc, char* argv[]);

  std::vector<SimpleEntity> m_Entities;
  uint64_t m_EntityNum;
};