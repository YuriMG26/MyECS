#include "ParticleScene.h"

#include "../Components.h"

ParticleScene::ParticleScene() : Scene() {}

ParticleScene::ParticleScene(const std::string &sceneName) : Scene(sceneName) {}

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

    // attract
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

    DrawRectangle(transform.position.x, transform.position.y, 3, 3,
                  particle.color);
  }
}
