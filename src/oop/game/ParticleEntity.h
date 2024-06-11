#pragma once

#include <random>

#include "../../../vendor/raylib/include/raylib.h"
#include "../../../vendor/raylib/include/raymath.h"

// #include "../../components/PhysicsComponent.h"
// #include "../../components/PositionComponent.h"
//
#include "PositionComponent.h"
#include "../GameObject.h"

class ColorComponent : public IComponent
{
public:
  ColorComponent(int r, int g, int b) { color.r = r; color.g = g; color.b = b; color.a =  255; }
  void operator=(const Color& other) { color.r = other.r; color.g = other.g; color.b = other.b; color.a = other.a; }
  void update(float delta) {}
  Color getColor() { return color ;}
  void setColor(Color color) { color = color; }
protected:
  Color color;
};

class ParticleEntity : public GameObject {
 public:

  ParticleEntity(const std::string& name, int x, int y, int r, int g, int b);

  ~ParticleEntity();

  void update(float delta);
  void draw();

  const std::string& getName() const { return m_Name; }

  void setMousePosition(Vector2 mousePosition) {
    m_MousePosition = mousePosition;
  }

  Color getColor(void) { return m_Color->getColor(); }
  void setColor(Color newColor);

  PositionComponent getPosition() const;
  void setPosition(Vector2 newPosition);

  PhysicsComponent getPhysics() const;
  void setVelocity(Vector2 newVelocity);

 private:
  std::string m_Name;

  std::vector<IComponent*> m_Components;
  ColorComponent    *m_Color;
  PhysicsComponent  *m_Physics;
  PositionComponent *m_Position;

  Vector2 m_MousePosition = {0};

  void makeStar();
  void makePlanet();
};
