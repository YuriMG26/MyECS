#include "Application.h"

Application::Application(int argc, char* argv[], const char* title, int width,
                         int height, bool lock_framerate_to_screen,
                         int target_fps)
    : m_Title(title), m_Width(width), m_Height(height) {
  this->parseArgs(argc, argv);
  Logger::log("Initializing window with dimensions %d x %d", width, height);
  InitWindow(width, height, title);
  if (lock_framerate_to_screen) {
    target_fps = GetMonitorRefreshRate(GetCurrentMonitor());
  }
  SetTargetFPS(target_fps);
  Logger::log("Application created successfully!");
}

Application::~Application() {
  // TODO: Cleanup
  CloseWindow();
}

void Application::run() {
  while (!WindowShouldClose()) {
    this->update();
    this->draw();
  }
}

void Application::setState(unsigned int flags) const { SetWindowState(flags); }

void Application::setTitle(const char* title) {
  SetWindowTitle(title);
  this->m_Title = title;
}

void Application::update() {
  // TODO: update
  // TODO: fixed update?
}

void Application::draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  EndDrawing();
}

void Application::parseArgs(int argc, char* argv[]) {
  if (argc > 64) {
    Logger::error("Invalid arg count!");
  }
}
