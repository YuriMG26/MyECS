#include "Scene.h"

#include "Components.h"
#include "Entity.h"

Scene::Scene() {
  m_SceneName = "Empty scene";
  auto entity = m_Registry.create();
}

Scene::Scene(const std::string &sceneName) : m_SceneName(sceneName) {
  Logger::log("initting scene \"%s\"", sceneName.c_str());
}

void Scene::update(float delta, Camera2D camera) {}

Entity Scene::CreateEntity(const std::string &name) {
  Entity entity = {m_Registry.create(), this};
  TransformComponent &transform = entity.AddComponent<TransformComponent>();
  transform.scale = 1.0;
  auto &tag = entity.AddComponent<TagComponent>();
  tag.tag = (name.empty()) ? "Empty entity" : name;
  return entity;
}

void Scene::DestroyEntity(Entity entity) { m_Registry.destroy(entity); }
