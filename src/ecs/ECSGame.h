#pragma once

#include <cstdint>

#include "GameState.h"

//
#include "../Application.h"

class ECSGame : public Application {
 public:
  ECSGame(int argc, char* argv[], const char* title = "Application",
          int width = 1280, int height = 720,
          bool lock_framerate_to_screen = false, int target_fps = 60);
  ~ECSGame();

  // void run();

  void update();
  void draw();

 private:
  GameState* m_GameState;

  uint8_t m_Mode;
  bool m_DebugMode;

  void parseArgs(int argc, char* argv[]);

  int m_ScreenWidth;
  int m_ScreenHeight;
  int m_ScreenX;
  int m_ScreenY;

  int m_EntityNum;

  bool m_Fullscreen = false;

  int m_TargetFPS;

  bool m_DrawGui = true;
  bool m_ShouldDraw = true;
  // bool m_PureCPUMode = false;
};
