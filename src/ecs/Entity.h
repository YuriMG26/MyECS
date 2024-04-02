#pragma once

#include <cstdint>

#include "../Logger.h"
#include "Scene.h"

class Entity {
 public:
  Entity() = default;
  Entity(entt::entity handle, Scene *scenePointer);
  Entity(const Entity &other) = default;

  template <typename Type>
  bool HasComponent() {
    return m_Scene->m_Registry.all_of<Type>(m_Entity);
  }

  template <typename Type, typename... Args>
  Type &AddComponent(Args &&...args) {
    if (HasComponent<Type>())
      // TODO: Arrumar logger
      Logger::error("%s: entity already has component", FUNCTION_SIGNATURE);
    return m_Scene->m_Registry.emplace<Type>(m_Entity,
                                             std::forward<Args>(args)...);
  }

  template <typename Type>
  Type &GetComponent() {
    return m_Scene->m_Registry.get<Type>(m_Entity);
  }

  template <typename Type>
  void RemoveComponent() {
    if (HasComponent<Type>())
      Logger::error("%s: entity does not have component.", FUNCTION_SIGNATURE);
    m_Scene->m_Registry.remove<Type>(m_Entity);
  }

  operator bool() const { return m_Entity != entt::null; };

  operator entt::entity() const { return m_Entity; }
  operator uint32_t() const { return (uint32_t)m_Entity; };
  bool operator==(const Entity &other) const {
    return m_Entity == other.m_Entity && m_Scene == other.m_Scene;
  }

  bool operator!=(const Entity &other) const {
    return m_Entity != other.m_Entity || m_Scene != other.m_Scene;
  }

 private:
  entt::entity m_Entity{entt::null};
  Scene *m_Scene = nullptr;
};
