#pragma once

#include <cstdint>

#include "GameState.h"

class ECSGame {
 public:
  ECSGame(int argc, char* argv[], int width, int height, const char* title,
          bool lockFPS);
  ~ECSGame();

  void run();

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
};
