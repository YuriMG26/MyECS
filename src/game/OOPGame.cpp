#include "OOPGame.h"

#include <algorithm>
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
  m_Entities.push_back(SimpleEntity("Star", true));

  // Creating remainder entities
  for (std::size_t i = 0; i < m_EntityNum; ++i) {
    Logger::log("Creating entity %d", i);

    char buffer[64];
    secure_sprintf(buffer, 64, "Planet #%d", i);
    m_Entities.push_back(SimpleEntity(buffer, false));
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

  Vector2 mouseDelta = GetMouseDelta();

  if (!ImGui::GetIO().WantCaptureMouse) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 cameraTargetGlobal =
          GetWorldToScreen2D(m_Camera.target, m_Camera);
      cameraTargetGlobal.x -= mouseDelta.x;
      cameraTargetGlobal.y -= mouseDelta.y;
      m_Camera.target = GetScreenToWorld2D(cameraTargetGlobal, m_Camera);
    }
    m_Camera.zoom += GetMouseWheelMove() * 0.1f;
    m_Camera.zoom = Clamp(m_Camera.zoom, 0.1, 20.0);
  }
}

void OOPGame::draw() {
  BeginDrawing();

  rlImGuiBegin();

  ClearBackground(RAYWHITE);

  BeginMode2D(m_Camera);
  for (SimpleEntity& e : m_Entities) {
    e.draw();
  }
  EndMode2D();

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
      m_EntityNum = entity_num;
      Logger::log("Successfully initializing game with %zu entities.",
                  m_EntityNum);
    }
  }
}

void OOPGame::draw_gui() {
  ImGui::Begin("Debug info");
  ImGui::Text("Mousepos = (%f, %f)", GetMousePosition().x,
              GetMousePosition().y);

  ImGui::Text("MouseDelta = (%f, %f)", GetMouseDelta().x, GetMouseDelta().y);
  int i = 0;

  // CAMERA
  if (ImGui::TreeNode("Camera")) {
    ImGui::DragFloat("CameraZoom", &m_Camera.zoom);

    float target[2] = {m_Camera.target.x, m_Camera.target.y};
    ImGui::DragFloat2("CameraZoom", target);
    m_Camera.target.x = target[0];
    m_Camera.target.x = target[1];
  }

  for (SimpleEntity& e : m_Entities) {
    // TODO: move e.draw to a different place
    // e.draw();
    auto position = e.getPosition();
    auto velocity = e.getPhysics().velocity;
    if (ImGui::TreeNode((void*)(intptr_t)i, "%s", e.getName().c_str())) {
      ImGui::Text("Position: (%f, %f)", position.x, position.y);
      ImGui::Text("Velocity: (%f, %f)", velocity.x, velocity.y);

      float v[2] = {velocity.x, velocity.y};
      ImGui::DragFloat2("Velocity", v);

      OrbitalComponent orbital = e.getOrbital();
      ImGui::DragFloat("Orbital mass", &orbital.mass);
      e.setOrbital(orbital);

      ImGui::TreePop();
    }
    ++i;
  }
  ImGui::End();
}
