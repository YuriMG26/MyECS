#pragma once

#include <random>

#include "../GameObject.h"
#include "../components/PhysicsComponent.h"
#include "../components/PositionComponent.h"

class SimpleEntity {
 public:
  SimpleEntity();
  ~SimpleEntity();

  void update(float delta);
  void draw();

  PositionComponent getPosition() const;
  void setPosition(Vector2 newPosition);

  PhysicsComponent getPhysics() const;
  void setVelocity(Vector2 newVelocity);

 private:
  Color m_Color;
  PhysicsComponent m_Physics;
  PositionComponent m_Position;
};