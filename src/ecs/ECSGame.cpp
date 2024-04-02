#include "ECSGame.h"

#include <sstream>
void StyleImGui();

ECSGame::ECSGame(int argc, char *argv[], int width, int height,
                 const char *title, bool matchFpsToRefreshRate)
    : m_ScreenWidth(width), m_ScreenHeight(height), m_EntityNum(256) {
  InitWindow(width, height, title);
  this->parseArgs(argc, argv);

  int currentMonitor = GetCurrentMonitor();

  // SetWindowState(FLAG_WINDOW_UNDECORATED);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowState(FLAG_MSAA_4X_HINT);

  if (m_Fullscreen) ToggleFullscreen();

  m_GameState = new GameState(m_EntityNum);

  if (matchFpsToRefreshRate) {
    int refreshRate = GetMonitorRefreshRate(currentMonitor);
    SetTargetFPS(refreshRate);
  }

  rlImGuiSetup(true);
  StyleImGui();
}

ECSGame::~ECSGame() { delete m_GameState; }

void ECSGame::run() {
  while (!WindowShouldClose() && !m_GameState->ShouldClose()) {
    BeginDrawing();
    rlImGuiBegin();
    ClearBackground(WHITE);
    m_GameState->tick();
    m_GameState->update();
    m_GameState->editor();
    m_GameState->render();
    rlImGuiEnd();
    EndDrawing();
  }
}

void ECSGame::parseArgs(int argc, char *argv[]) {
  if (argc > 64) {
    Logger::error("Invalid number of arguments! (over 64)");
  }
  if (argc == 1) return;
  for (int i = 1; i < argc; ++i) {
    std::string argument = argv[i];
    if (argument == "-entity" && i + 1 < argc) {
      i++;
      std::istringstream e(argv[i]);
      std::size_t entity_num;
      e >> entity_num;
      if (entity_num > SIZE_MAX) {
        Logger::log("Cannot initalize game with %zu entities", entity_num);
        continue;
      }
      m_EntityNum = entity_num;
      Logger::log("Successfully initializing game with %zu entities.",
                  m_EntityNum);
    }
  }
}
