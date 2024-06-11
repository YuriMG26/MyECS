#pragma once

#include <array>
#include "../IComponent.h"
#include "PhysicsComponent.h"

class PositionComponent : public IComponent
{
public:
  PositionComponent(int x, int y);
  void update(float delta);
  void setPhysics(Vector2);
  void setPosition(int, int);

  float& operator[](int index) { return position[index]; }

  std::array<float, 2> getPosition(void) { return this->position; }
protected:
  std::array<float, 2> position;
  Vector2 velocity;
};
