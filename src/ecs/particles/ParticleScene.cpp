#include "ParticleScene.h"

#include <random>

#include "../Components.h"
#include "../Entity.h"

ParticleScene::ParticleScene(uint32_t entity_num)
    : Scene(), m_EntityNum(entity_num) {
  InitParticleScene();
}

ParticleScene::ParticleScene(const std::string &sceneName, uint32_t entity_num)
    : Scene(sceneName), m_EntityNum(entity_num) {
  InitParticleScene();
}

void ParticleScene::update(float delta, Camera2D camera) {
  Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
  Vector2 differenceVector = {0};

  auto group =
      m_Registry.group<ParticleTag, TransformComponent, PhysicsComponent>();
  for (auto &e : group) {
    ParticleTag &particle = group.get<ParticleTag>(e);
    TransformComponent &transform = group.get<TransformComponent>(e);
    PhysicsComponent &physics = group.get<PhysicsComponent>(e);

    differenceVector.x = transform.position.x - mousePosition.x;
    differenceVector.y = transform.position.y - mousePosition.y;

    float dist = Vector2Distance({transform.position.x, transform.position.y},
                                 mousePosition);

    if (dist == 0.0f) dist = 1;
    Vector2 normal = {differenceVector.x * (1 / dist),
                      differenceVector.y * (1 / dist)};

    dist = fmax(dist, 0.5);
    physics.velocity.x -= normal.x / dist;
    physics.velocity.y -= normal.y / dist;

    physics.velocity.x *= 0.99;
    physics.velocity.y *= 0.99;

    transform.position.x += physics.velocity.x * 100 * delta;
    transform.position.y += physics.velocity.y * 100 * delta;

    auto screenWidth = GetScreenWidth();
    auto screenHeight = GetScreenHeight();

    if (transform.position.x < 0) transform.position.x += screenWidth;
    if (transform.position.x >= screenWidth)
      transform.position.x -= screenWidth;

    if (transform.position.y < 0) transform.position.y += screenHeight;
    if (transform.position.y >= screenHeight)
      transform.position.y -= screenHeight;

    if(!m_PureCPUMode)
      DrawRectangle(transform.position.x, transform.position.y, 3, 3,
                    particle.color);
  }
}

void ParticleScene::InitParticleScene() {
  std::random_device rd;   // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_int_distribution<> distrX(0, GetScreenWidth());
  std::uniform_int_distribution<> distrY(0, GetScreenHeight());
  std::uniform_int_distribution<> distrColor(0, 255);

  for (uint32_t i = 0; i < m_EntityNum; i++) {
    char buffer[128] = {};
    secure_sprintf(buffer, 128, "Square %d", i);
    auto e = CreateEntity(buffer);
    auto &particle = e.AddComponent<ParticleTag>();
    particle.color.r = distrColor(gen);
    particle.color.g = distrColor(gen);
    particle.color.b = distrColor(gen);
    particle.color.a = 255;

    e.AddComponent<PhysicsComponent>();

    e.GetComponent<TransformComponent>().position.x = distrX(gen);
    e.GetComponent<TransformComponent>().position.y = distrY(gen);
  }
}
