#pragma once

#include <random>


#include "../../components/PhysicsComponent.h"
#include "../../components/PositionComponent.h"
#include "../GameObject.h"

using ColorComponent = Color;

class ParticleEntity : public GameObject {
 public:

  ParticleEntity(const std::string& name, bool isStar);
  ~ParticleEntity();

  void update(float delta);
  void draw();

  const std::string& getName() const { return m_Name; }

  void setMousePosition(Vector2 mousePosition) {
    m_MousePosition = mousePosition;
  }

  Color getColor(void) const { return m_Color; }
  void setColor(Color newColor);

  PositionComponent getPosition() const;
  void setPosition(Vector2 newPosition);

  PhysicsComponent getPhysics() const;
  void setVelocity(Vector2 newVelocity);

 private:
  std::string m_Name;

  ColorComponent m_Color;
  PhysicsComponent m_Physics = {0};
  PositionComponent m_Position = {0};

  Vector2 m_MousePosition = {0};

  void makeStar();
  void makePlanet();
};
