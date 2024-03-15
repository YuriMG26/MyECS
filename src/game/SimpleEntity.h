#pragma once

#include <random>

#include "../components/OrbitalComponent.h"
#include "../components/PhysicsComponent.h"
#include "../components/PositionComponent.h"
#include "../oop/GameObject.h"

class SimpleEntity : public GameObject {
 public:
  SimpleEntity();
  ~SimpleEntity();

  void update(float delta);
  void draw();

  PositionComponent getPosition() const;
  void setPosition(Vector2 newPosition);

  PhysicsComponent getPhysics() const;
  void setVelocity(Vector2 newVelocity);

  OrbitalComponent getOrbital() const;
  void setOrbital(OrbitalComponent newOrbital);

  bool isStar() const { return m_IsStar; }

  void setEntityAsStar() { this->m_IsStar = true; }

  void setStar(const PositionComponent& position,
               const OrbitalComponent& orbital) {
    m_StarPosition = position;
    m_StarOrbital = orbital;
  }

 private:
  bool m_IsStar;
  Color m_Color;
  OrbitalComponent m_Orbital;
  PhysicsComponent m_Physics;
  PositionComponent m_Position;

  PositionComponent m_StarPosition;
  OrbitalComponent m_StarOrbital;
};
