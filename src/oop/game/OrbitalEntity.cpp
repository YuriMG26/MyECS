#include "OrbitalEntity.h"

#include <cmath>

void OrbitalEntity::makeStar() {
  m_Color = {0, 255, 255, 255};
  m_Position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
  m_Physics.velocity = {0, 0};
  m_Orbital.mass = 10e7;
  m_IsStar = true;
}

void OrbitalEntity::makePlanet() {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  Color color;
  std::uniform_int_distribution<unsigned int> r(0, 255);
  color.r = static_cast<unsigned char>(r(gen));

  std::uniform_int_distribution<unsigned int> g(0, 255);
  color.g = static_cast<unsigned char>(g(gen));

  std::uniform_int_distribution<unsigned int> b(0, 255);
  color.b = static_cast<unsigned char>(b(gen));

  color.a = 255;

  Vector2 position;
  std::uniform_real_distribution<float> posx(
      0.0f, static_cast<float>(GetScreenWidth() - 20));
  position.x = posx(gen);

  std::uniform_real_distribution<float> posy(
      0.0f, static_cast<float>(GetScreenHeight() - 20));
  position.y = posy(gen);

  m_IsStar = false;
  m_Position = {position.x, position.y};
  m_Orbital.mass = 10e3;
  m_Physics = {0};
  m_Color = color;
}

OrbitalEntity::OrbitalEntity(const std::string& name, bool isStar) {
  m_Name = name;
  if (isStar) {
    makeStar();
  } else {
    makePlanet();
  }
}

OrbitalEntity::~OrbitalEntity() {}

void OrbitalEntity::update(float delta) {
  constexpr float gravitational = 6.6743e-11;

  Vector2 differenceVector;

  if (!m_IsStar) {
    differenceVector.x = m_Position.x - m_MousePosition.x;
    differenceVector.y = m_Position.y - m_MousePosition.y;

    float dist = Vector2Distance({m_Position.x, m_Position.y}, m_MousePosition);

    // TODO: separar isso em várias funções
    if (dist == 0.0f) dist = 1;
    Vector2 normal = {differenceVector.x * (1 / dist),
                      differenceVector.y * (1 / dist)};

    // attract
    dist = fmax(dist, 0.5);
    m_Physics.velocity.x -= normal.x / dist;
    m_Physics.velocity.y -= normal.y / dist;

    m_Physics.velocity.x *= 0.99;
    m_Physics.velocity.y *= 0.99;

    // m_FinalVector = planetVelocity;
    m_Position.x += m_Physics.velocity.x * 100 * delta;
    m_Position.y += m_Physics.velocity.y * 100 * delta;

    auto screenWidth = GetScreenWidth();
    auto screenHeight = GetScreenHeight();

    if (m_Position.x < 0) m_Position.x += screenWidth;
    if (m_Position.x >= screenWidth) m_Position.x -= screenWidth;

    if (m_Position.y < 0) m_Position.y += screenHeight;
    if (m_Position.y >= screenHeight) m_Position.y -= screenHeight;
  }
}

void OrbitalEntity::draw() {
  constexpr int size = 3;
  DrawRectangle(this->m_Position.x, this->m_Position.y, size, size, m_Color);
  // DrawLineEx({m_Position.x, m_Position.y},
  //            {m_Position.x + m_Physics.velocity.x,
  //             m_Position.y + m_Physics.velocity.y},
  //            1.0f, ORANGE);
}

PositionComponent OrbitalEntity::getPosition() const { return m_Position; }

void OrbitalEntity::setPosition(Vector2 newPosition) {
  this->m_Position.x = newPosition.x;
  this->m_Position.y = newPosition.y;
}

PhysicsComponent OrbitalEntity::getPhysics() const { return m_Physics; }

void OrbitalEntity::setVelocity(Vector2 newVelocity) {
  this->m_Physics.velocity = newVelocity;
}

OrbitalComponent OrbitalEntity::getOrbital() const { return m_Orbital; }

void OrbitalEntity::setOrbital(OrbitalComponent newOrbital) {
  this->m_Orbital = newOrbital;
}
