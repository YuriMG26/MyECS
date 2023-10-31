#include "OOPGame.h"

OOPGame::OOPGame(int argc, char* argv[], const char* title, int width,
                 int height, bool lock_framerate_to_screen, int target_fps)
    : Application(argc, argv, title, width, height, lock_framerate_to_screen,
                  target_fps),
      m_EntityNum(16) {
  parseArgs(argc, argv);
  for (uint64_t i; i < m_EntityNum; ++i) {
    m_Entities.push_back(SimpleEntity());
  }
}

OOPGame::~OOPGame() {
  // NOTE: Don't call CloseWindow :p
}

void OOPGame::run() {
  while (not WindowShouldClose()) {
    this->update();
    this->draw();
  }
}

void OOPGame::update() {
  this->m_Delta = GetFrameTime();

  for (SimpleEntity& e : m_Entities) {
    e.update(this->m_Delta);
  }
}

void OOPGame::draw() {
  BeginDrawing();
  rlImGuiBegin();

  ClearBackground(RAYWHITE);

  for (SimpleEntity e : m_Entities) {
    e.draw();
  }

  char text[256];
  auto position = m_Entities[0].getPosition();
  sprintf_s(text, 256, "%f %f", position.x, position.y);
  DrawText(text, 10, 30, 20, RED);

  auto physics = m_Entities[0].getPhysics();
  sprintf_s(text, 256, "%f %f", physics.velocity.x, physics.velocity.y);
  DrawText(text, 10, 65, 20, RED);

  DrawFPS(10, 10);

  static bool open = true;
  ImGui::ShowDemoWindow(&open);

  rlImGuiEnd();
  EndDrawing();
}

void OOPGame::parseArgs(int argc, char* argv[]) {
  if (argc > 64) {
    Logger::error("Invalid number of arguments! (over 64)");
  }
  if (argc == 1) return;
  for (int i = 1; i < argc; ++i) {
    std::string argument = argv[i];
    if (argument == "-entity" && i + 1 < argc) {
      std::istringstream e(argv[i + 1]);
      if (e >> m_EntityNum) {
        i++;
        Logger::log("Successfully initializing game with %zu entities.",
                    m_EntityNum);
      }
    }
  }
}
