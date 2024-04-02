#include "GameState.h"

#include "Components.h"
#include "particles/ParticleScene.h"

GameState::GameState(uint32_t entity_num) {
  m_Camera = {{(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2},
              {0, 0},
              0.0,
              1.0};

  m_CurrentScene = new ParticleScene("Scene 1", entity_num);
}

void GameState::tick() {
  m_FramesPerSecond = GetFPS();
  m_FrameTime = GetFrameTime();
  m_TimeElapsed = GetTime();
  m_ScreenWidth = GetScreenWidth();
  m_ScreenHeight = GetScreenHeight();
  m_MousePosition = GetMousePosition();
  m_MouseDelta = GetMouseDelta();
}

void GameState::update() {
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 cameraTargetGlobal =
          GetWorldToScreen2D(m_Camera.target, m_Camera);
      cameraTargetGlobal.x -= m_MouseDelta.x;
      cameraTargetGlobal.y -= m_MouseDelta.y;
      m_Camera.target = GetScreenToWorld2D(cameraTargetGlobal, m_Camera);
    }
    m_Camera.zoom += GetMouseWheelMove() * 0.1f;
    m_Camera.zoom = std::clamp<float>(m_Camera.zoom, 0.1, 20.0);
  }
}

void GameState::render() {
  BeginMode2D(m_Camera);
  m_CurrentScene->update(m_FrameTime, m_Camera);
  EndMode2D();
}

void GameState::editor() {
  // ImGui::ShowDemoWindow();

  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu(ICON_FK_COG "AWON")) {
      if (ImGui::MenuItem("Exit", "ESC")) m_ShouldClose = true;
      ImGui::EndMenu();
    }
    ImGui::SameLine(ImGui::GetWindowWidth() - 40);
    if (ImGui::Button(ICON_FK_TIMES)) m_ShouldClose = true;
    ImGui::EndMainMenuBar();
  }

  ImGui::SetNextWindowPos({0, 23});
  ImGui::Begin("Menu0", NULL, ImGuiWindowFlags_NoTitleBar);
  if (ImGui::CollapsingHeader(ICON_FK_MICROCHIP " Engine Core Info")) {
    ImGui::Text("\t" ICON_FK_DESKTOP " Window dimensions: %i x %i",
                m_ScreenWidth, m_ScreenHeight);
    ImGui::Text("\t" ICON_FK_CLOCK_O " Frames per Second: %d",
                m_FramesPerSecond);
    ImGui::Text("\t" ICON_FK_CLOCK_O " Frametime: %f", m_FrameTime);
    ImGui::Text("\t" ICON_FK_HOURGLASS " Time elapsed: %lf", m_TimeElapsed);
    if (ImGui::TreeNode(ICON_FK_MOUSE_POINTER " Mouse Info")) {
      ImGui::Text("\tPosition: %f %f", m_MousePosition.x, m_MousePosition.y);
      ImGui::Text("\tDelta: %f %f", m_MouseDelta.x, m_MouseDelta.y);
      ImGui::TreePop();
    }

    if (ImGui::TreeNode(ICON_FK_CAMERA " Camera Info")) {
      ImGui::Text("\tTarget: %f %f", m_Camera.target.x, m_Camera.target.y);
      ImGui::Text("\tOffset: %f %f", m_Camera.offset.x, m_Camera.offset.y);
      ImGui::Text("\tZoom: %f", m_Camera.zoom);
      if (ImGui::Button("Reset zoom")) {
        m_Camera.zoom = 1.0;
      }
      ImGui::TreePop();
    }
  }

  if (ImGui::CollapsingHeader(ICON_FK_USERS " Entities")) {
    for (auto [e] : m_CurrentScene->m_Registry.storage<entt::entity>().each()) {
      Entity entity{e, m_CurrentScene};
      DrawEntityNode(entity);
    }

    ImGui::Begin("Properties");
    if (m_SelectionContext) {
      DrawComponents(m_SelectionContext);

      if (ImGui::Button("Add Component")) {
        ImGui::OpenPopup("AddComponent");
      }

      if (ImGui::BeginPopup("AddComponent")) {
        if (ImGui::MenuItem("Camera")) {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
    }

    ImGui::End();
  }
  ImGui::End();
}

void GameState::DrawEntityNode(Entity entity) {
  auto& tag = entity.GetComponent<TagComponent>().tag;
  ImGuiTreeNodeFlags flags =
      ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
      ImGuiTreeNodeFlags_OpenOnArrow;
  flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
  bool opened =
      ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
  if (ImGui::IsItemClicked()) {
    m_SelectionContext = entity;
  }

  if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
    m_SelectionContext = {};
  }

  bool entityDeleted = false;
  if (ImGui::BeginPopupContextItem()) {
    if (ImGui::MenuItem("Delete Entity")) entityDeleted = true;

    ImGui::EndPopup();
  }

  if (opened) {
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
    if (opened) ImGui::TreePop();
    ImGui::TreePop();
  }

  if (entityDeleted) {
    m_CurrentScene->DestroyEntity(entity);
    if (m_SelectionContext == entity) m_SelectionContext = {};
  }
}

void GameState::DrawComponents(Entity entity) {
  if (entity.HasComponent<TagComponent>()) {
    auto& tag = entity.GetComponent<TagComponent>().tag;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy_s(buffer, 256, tag.c_str());
    if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
      tag = std::string(buffer);
    }
  } else {
    Logger::error("entity doesn't have tag component.");
  }
  if (entity.HasComponent<TransformComponent>()) {
    auto& transform = entity.GetComponent<TransformComponent>();
    ImGui::DragFloat2("Position", (float*)&transform.position, 0.5f, -1'000'000,
                      +1'000'000);
  }
  // TODO: check this
#if 0
    auto& transform = entity.GetComponent<TransformComponent>();
    ImGui::SliderFloat2("Position", (float*)&transform.position, -10000,
        10000);
    ImGui::DragFloat("Rotation", &transform.rotation);
    ImGui::DragFloat("Scale", &transform.scale);
    // ImGui::Button("Delete Entity", {0xF4, 0x56, 0x55, 0xFF});
    ImGui::Button("Delete Entity");


    ImGui::TreePop();
#endif
}
