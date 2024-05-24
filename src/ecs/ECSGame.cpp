#include "ECSGame.h"

#include <sstream>
void StyleImGui();

ECSGame::ECSGame(int argc, char* argv[], const char* title, int width,
                 int height, bool lock_framerate_to_screen, int target_fps)
    : Application(argc, argv, title, width, height, lock_framerate_to_screen,
                  target_fps),
      m_ScreenWidth(width),
      m_ScreenHeight(height),
      m_EntityNum(256) {
  this->parseArgs(argc, argv);
  m_GameState = new GameState(m_EntityNum);
}

ECSGame::~ECSGame() { delete m_GameState; }

void ECSGame::update() {
  if (IsKeyPressed(KEY_F1)) m_DrawGui = !m_DrawGui;
  m_GameState->tick();
  m_GameState->update();
}

void ECSGame::draw() {
  BeginDrawing();
  if (m_DrawGui)
    rlImGuiBegin();
  ClearBackground(WHITE);
  m_GameState->render();
  if (m_DrawGui)
    m_GameState->editor();
  else
    DrawFPS(10, 10);
  if (m_DrawGui)
    rlImGuiEnd();
  else
    DrawText("PURE CPU MODE", GetScreenWidth() / 2 - (MeasureText("PURE CPU MODE", 40) / 2), GetScreenHeight() / 2, 40, BLACK);
  EndDrawing();
}

void ECSGame::parseArgs(int argc, char* argv[]) {
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
    else if (argument == "-purecpu") {
      m_ShouldDraw = false;
      m_DrawGui = false;
      m_PureCPUMode = true;
      m_GameState->pureCpuMode(true);
    }
  }
}
