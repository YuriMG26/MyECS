#include "../IComponent.h"

class PhysicsComponent : public IComponent
{
public:
  PhysicsComponent() { velocity = {0}; }
  PhysicsComponent(float x, float y) {}

  void update(float delta) {
  }
  
  void updateValues(Vector2 normal, float dist)
  {
    velocity.x -= normal.x / dist;
    velocity.y -= normal.y / dist;

    velocity.x *= 0.99;
    velocity.y *= 0.99;
  }

  Vector2 getVelocity(void) { return velocity; }
  void setVelocity(Vector2 v) { velocity = v; }
  
protected:
  Vector2 velocity;
};
