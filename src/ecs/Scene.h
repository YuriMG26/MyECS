#pragma once

#include <string>

#include "../../vendor/entt/entity/registry.hpp"
#include "../../vendor/raylib/include/raylib.h"
//
#include "../../vendor/raylib/include/raymath.h"

class Entity;

class Scene {
 public:
  Scene();
  Scene(const std::string& sceneName);

  virtual void update(float delta, Camera2D camera);

  const entt::registry& Reg() const { return m_Registry; }
  Entity CreateEntity(const std::string& name = std::string());
  void DestroyEntity(Entity entity);

  inline void PureCPUMode(void) { m_PureCPUMode = true; }
  bool PureCPUMode(void) const { return m_PureCPUMode; }

 protected:
  std::string m_SceneName;
  entt::registry m_Registry;

  // TODO: make pure cpu mode togglable
  bool m_PureCPUMode = true;

  friend class Entity;
  friend class GameState;
};
