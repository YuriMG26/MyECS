#include "OOPGame.h"

#include <cstddef>
#include <cstdint>

OOPGame::OOPGame(int argc, char* argv[], const char* title, int width,
                 int height, bool lock_framerate_to_screen, int target_fps)
    : Application(argc, argv, title, width, height, lock_framerate_to_screen,
                  target_fps),
      m_EntityNum(1024) {
  parseArgs(argc, argv);
  Logger::log("Initializing game with %zu entities", m_EntityNum);

  m_Entities.reserve(m_EntityNum);

  // Creating star
  // Logger::log("Creating entity %d", 0);
  // m_Entities.push_back(ParticleEntity("Star", true));

  // Creating remainder entities
  for (std::size_t i = 0; i < m_EntityNum; ++i) {
    // Logger::log("Creating entity %d", i);

    char buffer[64];
    secure_sprintf(buffer, 64, "Planet #%d", i);
    m_Entities.push_back(ParticleEntity(buffer, false));
  }

  m_StarEntity = 0;
}

OOPGame::~OOPGame() {
  // NOTE: Don't call CloseWindow :p
}

void OOPGame::update() {
  // process key info
  #if 0
  if (IsKeyPressed(KEY_F1)) {
    m_DrawGui = !m_DrawGui;
  }
  if (IsKeyPressed(KEY_F2)) {
    m_ShouldDraw = !m_ShouldDraw;
  }

  this->m_Delta = GetFrameTime();
  #endif

  Vector2 mousePosition = GetMousePosition();
  mousePosition = GetScreenToWorld2D(mousePosition, m_Camera);

  for (ParticleEntity& e : m_Entities) {
    e.setMousePosition(mousePosition);
    e.update(this->m_Delta);
  }

  #if 0
  if (!m_PureCPUMode) {
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
  #endif
}

// TODO: better functions for dispatching between normal-mode and purecpu-mode
void OOPGame::draw() {
  BeginDrawing();

  if(m_DrawGui)
    rlImGuiBegin();

  ClearBackground(RAYWHITE);

  if (!m_PureCPUMode) {
    BeginMode2D(m_Camera);
    for (ParticleEntity& e : m_Entities) {
      e.draw();
    }
  }

  // TODO: remove debug bounds?
  #if 0
  Rectangle debugBounds = {0, 0, (float)GetScreenWidth(),
                           (float)GetScreenHeight()};
  DrawRectangleLinesEx(debugBounds, 2.0, RED);
  #endif

  if (!m_PureCPUMode)
    EndMode2D();
  // else
    // DrawText("PURE CPU MODE", GetScreenWidth() / 2 - (MeasureText("PURE CPU MODE", 40) / 2), GetScreenHeight() / 2, 40, BLACK);

  if (m_DrawGui)
    draw_gui();
  else
    DrawFPS(10, 10);

  if (m_DrawGui)
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
    else if(argument == "-purecpu") {
      m_ShouldDraw = false;
      m_DrawGui = false;
      m_PureCPUMode = true;
    }
  }
}

void OOPGame::draw_gui() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu(ICON_FK_COG "Sandbox")) {
      ImGui::Checkbox("Lock Framerate", &m_LockFramerate);
      ImGui::DragInt("Framerate Target", &m_FramerateTarget);

      if (ImGui::MenuItem("Exit", "ESC")) m_ShouldClose = true;
      ImGui::EndMenu();
    }
    ImGui::SameLine(ImGui::GetWindowWidth() - 40);
    if (ImGui::Button(ICON_FK_TIMES)) m_ShouldClose = true;
    ImGui::EndMainMenuBar();
  }

  ImGui::Begin("Debug info", NULL, ImGuiWindowFlags_NoTitleBar);
  if (ImGui::CollapsingHeader(ICON_FK_MICROCHIP " Engine Core Info")) {
    ImGui::Text("%d", GetFPS());
    ImGui::Text("Mousepos = (%f, %f)", GetMousePosition().x,
                GetMousePosition().y);

    ImGui::Text("MouseDelta = (%f, %f)", GetMouseDelta().x, GetMouseDelta().y);

    // CAMERA
    if (ImGui::TreeNode("Camera")) {
      ImGui::DragFloat("Zoom", &m_Camera.zoom);

      float target[2] = {m_Camera.target.x, m_Camera.target.y};
      ImGui::DragFloat2("Target", target);
      m_Camera.target.x = target[0];
      m_Camera.target.y = target[1];

      float offset[2] = {m_Camera.offset.x, m_Camera.offset.y};
      ImGui::DragFloat2("Offset", offset);
      m_Camera.offset.x = offset[0];
      m_Camera.offset.y = offset[1];

      ImGui::TreePop();
    }
  }

  if (ImGui::CollapsingHeader(ICON_FK_USERS " Entities")) {
    int i = 0;
    for (ParticleEntity& e : m_Entities) {
      auto position = e.getPosition();
      auto velocity = e.getPhysics().velocity;
      if (ImGui::TreeNode((void*)(intptr_t)i, "%s", e.getName().c_str())) {
        ImGui::Text("Position: (%f, %f)", position.x, position.y);
        ImGui::Text("Velocity: (%f, %f)", velocity.x, velocity.y);

        float v[2] = {velocity.x, velocity.y};
        ImGui::DragFloat2("Velocity", v);
        e.setVelocity({v[0], v[1]});

        ImGui::TreePop();
      }
      ++i;
    }
  }
  ImGui::End();
}
