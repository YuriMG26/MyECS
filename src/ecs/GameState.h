#pragma once

#include "../../vendor/raylib/include/imgui.h"
//
#include "../../vendor/raylib/include/rlImGui.h"
//
#include "../../vendor/raylib/include/extras/IconsForkAwesome.h"
#include "Entity.h"

class GameState {
 public:
  GameState(uint32_t entity_num);
  ~GameState() { delete m_CurrentScene; };

  void tick();
  void update();
  void render();

  bool ShouldClose() const { return m_ShouldClose; }

  // void pureCpuMode(bool pureCpuMode);
  // bool pureCpuMode(void) const { return m_PureCPUMode; }

  // TODO: Standardize the editor for both games
  void editor();

 private:
  void DrawEntityNode(Entity entity);
  void DrawComponents(Entity entity);

  bool m_ShouldClose = false;
  // bool m_PureCPUMode = false;

  int m_ScreenX, m_ScreenY;
  int m_ScreenWidth, m_ScreenHeight;
  int m_FramesPerSecond;
  float m_FrameTime;
  double m_TimeElapsed;

  Vector2 m_MousePosition;
  Vector2 m_MouseDelta;

  Camera2D m_Camera;

  Entity m_SelectionContext;

  

  Scene *m_CurrentScene;
};
