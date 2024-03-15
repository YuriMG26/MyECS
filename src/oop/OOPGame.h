#pragma once

#include <cstddef>
#include <sstream>

#include "../Application.h"
#include "../game/SimpleEntity.h"

class OOPGame : public Application {
 public:
  OOPGame(int argc, char* argv[], const char* title = "Application",
          int width = 1280, int height = 720,
          bool lock_framerate_to_screen = false, int target_fps = 60);
  ~OOPGame();
  void run();

 private:
  void update();
  void draw();
  void draw_gui();
  void parseArgs(int argc, char* argv[]);

  std::vector<SimpleEntity> m_Entities;
  std::size_t m_EntityNum;
  std::size_t m_StarEntity;
};
