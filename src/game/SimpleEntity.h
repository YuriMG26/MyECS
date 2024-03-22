#pragma once

#include <random>

#include "../components/OrbitalComponent.h"
#include "../components/PhysicsComponent.h"
#include "../components/PositionComponent.h"
#include "../oop/GameObject.h"

class SimpleEntity : public GameObject {
 public:
  SimpleEntity(const std::string& name, bool isStar);
  ~SimpleEntity();

  void update(float delta);
  void draw();

  const std::string& getName() const { return m_Name; }

  Color getColor(void) const { return m_Color; }
  void setColor(Color newColor);

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
  std::string m_Name;

  bool m_IsStar;
  Color m_Color;
  OrbitalComponent m_Orbital = {0};
  PhysicsComponent m_Physics = {0};
  PositionComponent m_Position = {0};

  PositionComponent m_StarPosition = {0};
  OrbitalComponent m_StarOrbital = {0};

  // Gravity simulation
  Vector2 m_FinalVector = {0};
  Vector2 m_GravityVector = {0};
  float m_GravityIntensity = 0;

  void makeStar();
  void makePlanet();
};
