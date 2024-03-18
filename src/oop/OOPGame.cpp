#include "OOPGame.h"

#include <cstddef>
#include <cstdint>

OOPGame::OOPGame(int argc, char* argv[], const char* title, int width,
                 int height, bool lock_framerate_to_screen, int target_fps)
    : Application(argc, argv, title, width, height, lock_framerate_to_screen,
                  target_fps),
      m_EntityNum(16) {
  parseArgs(argc, argv);
  Logger::log("Initializing game with %zu entities", m_EntityNum);

  // Creating star
  Logger::log("Creating entity %d", 0);
  m_Entities.push_back(SimpleEntity(true));

  // Creating remainder entities
  for (std::size_t i = 0; i < m_EntityNum; ++i) {
    Logger::log("Creating entity %d", i);
    m_Entities.push_back(SimpleEntity(false));
  }

  m_StarEntity = 0;
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
  const SimpleEntity& star = m_Entities.at(0);

  for (SimpleEntity& e : m_Entities) {
    if (!e.isStar()) e.setStar(star.getPosition(), star.getOrbital());
    e.update(this->m_Delta);
  }
}

void OOPGame::draw() {
  BeginDrawing();
  rlImGuiBegin();

  ClearBackground(RAYWHITE);

  draw_gui();
  DrawFPS(10, 10);

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
      i++;
      std::istringstream e(argv[i]);
      std::size_t entity_num;
      e >> entity_num;
      if (entity_num > SIZE_MAX) {
        Logger::log("Cannot initalize game with %zu entities", entity_num);
        continue;
      }
      Logger::log("Successfully initializing game with %zu entities.",
                  m_EntityNum);
    }
  }
}

void OOPGame::draw_gui() {
  ImGui::Begin("Debug info");
  ImGui::Text("Mousepos = (%f, %f)", GetMousePosition().x,
              GetMousePosition().y);
  int i = 0;
  for (SimpleEntity e : m_Entities) {
    e.draw();
    auto position = e.getPosition();
    auto velocity = e.getPhysics().velocity;
    if (ImGui::TreeNode((void*)(intptr_t)i, "Entity [%d]", i)) {
      ImGui::Text("Position: (%f, %f)", position.x, position.y);
      ImGui::Text("Velocity: (%f, %f)", velocity.x, velocity.y);
      ImGui::TreePop();
    }
    ++i;
  }
  ImGui::End();
}
