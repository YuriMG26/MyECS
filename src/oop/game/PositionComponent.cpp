#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y)
{
  position[0] = x;
  position[1] = y;
}

void PositionComponent::setPosition(int x, int y)
{
  position[0] = x;
  position[1] = y;
}

void PositionComponent::update(float delta)
{
   position[0] += velocity.x * 100 * delta;
   position[1] += velocity.y * 100 * delta;
}

void PositionComponent::setPhysics(Vector2 v)
{
  velocity = v;
}

