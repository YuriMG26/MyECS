#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <array>
#include <string>
#include <string_view>

#include "../vendor/raylib/include/raylib.h"
//
#include "../vendor/raylib/include/imgui.h"
#include "../vendor/raylib/include/rlImGui.h"
//
#include "../vendor/raylib/include/ImGuiUtils.h"
//
#include "../vendor/raylib/include/extras/IconsForkAwesome.h"
#include "Logger.h"

class Application {
 public:
  Application(int argc, char* argv[], const char* title = "Application",
              int width = 1280, int height = 720,
              bool lock_framerate_to_screen = false, int target_fps = 60);
  ~Application();

  void run();
  void setState(unsigned int flags) const;
  void setTitle(const char* title);

 protected:
  virtual void update();
  virtual void draw();
  virtual void parseArgs(int argc, char* argv[]);

  int m_FramerateTarget = 60;
  bool m_LockFramerate;
  bool m_ShouldClose;
  float m_Delta;
  int m_Width;
  int m_Height;
  std::string m_Title;

  Camera2D m_Camera;
};
