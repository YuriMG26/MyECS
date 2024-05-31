#include "ParticleEntity.h"

#include <cmath>


ParticleEntity::ParticleEntity(const std::string& name, bool isStar) {
  m_Name = name;
}

ParticleEntity::~ParticleEntity() {}

void ParticleEntity::update(float delta) {
  Vector2 differenceVector;

  differenceVector.x = m_Position.x - m_MousePosition.x;
  differenceVector.y = m_Position.y - m_MousePosition.y;

  float dist = Vector2Distance({m_Position.x, m_Position.y}, m_MousePosition);

  if (dist == 0.0f) dist = 1;
  Vector2 normal = {differenceVector.x * (1 / dist),
                    differenceVector.y * (1 / dist)};

  dist = fmax(dist, 0.5);
  m_Physics.velocity.x -= normal.x / dist;
  m_Physics.velocity.y -= normal.y / dist;

  m_Physics.velocity.x *= 0.99;
  m_Physics.velocity.y *= 0.99;

  m_Position.x += m_Physics.velocity.x * 100 * delta;
  m_Position.y += m_Physics.velocity.y * 100 * delta;

  auto screenWidth = GetScreenWidth();
  auto screenHeight = GetScreenHeight();

  if (m_Position.x < 0) m_Position.x += screenWidth;
  if (m_Position.x >= screenWidth) m_Position.x -= screenWidth;

  if (m_Position.y < 0) m_Position.y += screenHeight;
  if (m_Position.y >= screenHeight) m_Position.y -= screenHeight;
}

void ParticleEntity::draw() {
  constexpr int size = 3;
  DrawRectangle(this->m_Position.x, this->m_Position.y, size, size, m_Color);
}

PositionComponent ParticleEntity::getPosition() const { return m_Position; }

void ParticleEntity::setPosition(Vector2 newPosition) {
  this->m_Position.x = newPosition.x;
  this->m_Position.y = newPosition.y;
}

PhysicsComponent ParticleEntity::getPhysics() const { return m_Physics; }

void ParticleEntity::setVelocity(Vector2 newVelocity) {
  this->m_Physics.velocity = newVelocity;
}
