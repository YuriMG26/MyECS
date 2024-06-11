#include "ParticleEntity.h"

#include <cmath>


ParticleEntity::ParticleEntity(const std::string& name, int x, int y, int r, int g, int b) 
{
  m_Color = new ColorComponent(r, g, b);
  m_Position = new PositionComponent(x, y);
  m_Physics = new PhysicsComponent();
  m_Name = name;
}

ParticleEntity::~ParticleEntity() {}

void ParticleEntity::update(float delta) {
  Vector2 differenceVector;

  auto position = m_Position->getPosition();
  auto velocity = m_Physics->getVelocity();

  differenceVector.x = position[0] - m_MousePosition.x;
  differenceVector.y = position[1] - m_MousePosition.y;

  // differenceVector.x = m_Position.x - 0;
  // differenceVector.y = position[1] - 0;

  float dist = Vector2Distance({position[0], position[1]}, m_MousePosition);

  if (dist == 0.0f) dist = 1;
  Vector2 normal = {differenceVector.x * (1 / dist),
                    differenceVector.y * (1 / dist)};

  dist = fmax(dist, 0.5);

  m_Physics->updateValues(normal, dist);
  m_Physics->update(delta);

  m_Position->setPhysics(m_Physics->getVelocity());
  m_Position->update(delta);
  
  auto screenWidth = GetScreenWidth();
  auto screenHeight = GetScreenHeight();

  if ((*m_Position)[0] < 0) 
    (*m_Position)[0] += screenWidth;
  if ((*m_Position)[0] >= screenWidth) (*m_Position)[0] -= screenWidth;

  if ((*m_Position)[1] < 0) (*m_Position)[1] += screenHeight;
  if ((*m_Position)[1] >= screenHeight) (*m_Position)[1] -= screenHeight;

  // m_Position.setPosition(position[0], position[1]);
  // m_Physics.setVelocity(velocity);
}

void ParticleEntity::draw() {
  std::array<float, 2> position = m_Position->getPosition();
  constexpr int size = 3;
  DrawRectangle(position.at(0), position.at(1), size, size, m_Color->getColor());
}

PositionComponent ParticleEntity::getPosition() const { return (*m_Position); }

void ParticleEntity::setPosition(Vector2 newPosition) {
  m_Position->setPosition(newPosition.x, newPosition.y);
}

PhysicsComponent ParticleEntity::getPhysics() const { return (*m_Physics); }

void ParticleEntity::setVelocity(Vector2 newVelocity) {
  m_Physics->setVelocity(newVelocity);
}
