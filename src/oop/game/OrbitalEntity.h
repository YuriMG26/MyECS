#pragma once

#include <random>

#include "../../components/OrbitalComponent.h"
#include "../../components/PhysicsComponent.h"
#include "../../components/PositionComponent.h"
#include "../GameObject.h"

class OrbitalEntity : public GameObject {
 public:
  OrbitalEntity(const std::string& name, bool isStar);
  ~OrbitalEntity();

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

  OrbitalComponent getOrbital() const;
  void setOrbital(OrbitalComponent newOrbital);

  bool isStar() const { return m_IsStar; }

  void setEntityAsStar() { this->m_IsStar = true; }

 private:
  std::string m_Name;

  bool m_IsStar;
  Color m_Color;
  OrbitalComponent m_Orbital = {0};
  PhysicsComponent m_Physics = {0};
  PositionComponent m_Position = {0};

  Vector2 m_MousePosition = {0};

  void makeStar();
  void makePlanet();
};