#include "SimpleEntity.h"

#include <cstdint>

void SimpleEntity::makeStar() {
  m_Color = {0, 255, 255, 255};
  m_Position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
  m_Physics.velocity = {0, 0};
  m_Orbital.mass = 10e7;
  m_IsStar = true;
}

void SimpleEntity::makePlanet() {
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

  PhysicsComponent physics;
  std::uniform_real_distribution<float> velx(-40.0f, +40.0f);
  std::uniform_real_distribution<float> vely(-40.0f, +40.0f);
  physics.velocity = {velx(gen), vely(gen)};

  m_IsStar = false;
  m_Position = {position.x, position.y};
  m_Orbital.mass = 10e3;
  m_Physics = physics;
  m_Color = color;
}

SimpleEntity::SimpleEntity(const std::string& name, bool isStar) {
  m_Name = name;
  if (isStar) {
    makeStar();
  } else {
    makePlanet();
  }
}

SimpleEntity::~SimpleEntity() {}

void SimpleEntity::update(float delta) {
  constexpr float gravitational = 6.6743e-11;

  if (!m_IsStar) {
    m_GravityVector.x = m_StarPosition.x - m_Position.x;
    m_GravityVector.y = m_StarPosition.y - m_Position.y;
    float radius = Vector2Length(m_GravityVector) / 10;
    m_GravityIntensity = (100 / (radius / 2)) / 10;
    m_GravityIntensity = Clamp(m_GravityIntensity, -18.8, 18.8);
    m_GravityVector =
        Vector2Scale(Vector2Normalize(m_GravityVector), m_GravityIntensity);

    if (m_Position.x >= GetScreenWidth()) {
      m_Position.x = GetScreenWidth();
      m_Physics.velocity.x *= -1;
    }
    if (m_Position.x <= 0) {
      m_Position.x = 0;
      m_Physics.velocity.x *= -1;
    }

    if (m_Position.y >= GetScreenHeight()) {
      m_Position.y = GetScreenHeight();
      m_Physics.velocity.y *= -1;
    }
    if (m_Position.y <= 0) {
      m_Position.y = 0;
      m_Physics.velocity.y *= -1;
    }

    Vector2 planetVelocity = {m_Physics.velocity.x, m_Physics.velocity.y};

    m_FinalVector = Vector2Add(planetVelocity, m_GravityVector);

    m_Position.x += m_FinalVector.x * GetFrameTime();
    m_Position.y += m_FinalVector.y * GetFrameTime();
  }
}

void SimpleEntity::draw() {
  // TODO: polymorphism for star
  int size = 3;
  if (m_IsStar) size = 20;
  DrawRectangle(this->m_Position.x, this->m_Position.y, size, size, m_Color);
  DrawLineEx({m_Position.x, m_Position.y},
             {m_Position.x + m_Physics.velocity.x,
              m_Position.y + m_Physics.velocity.y},
             1.0f, ORANGE);
  DrawLineEx(
      {m_Position.x, m_Position.y},
      {m_Position.x + m_GravityVector.x, m_Position.y + m_GravityVector.y},
      1.0f, BLUE);
}

PositionComponent SimpleEntity::getPosition() const { return m_Position; }

void SimpleEntity::setPosition(Vector2 newPosition) {
  this->m_Position.x = newPosition.x;
  this->m_Position.y = newPosition.y;
}

PhysicsComponent SimpleEntity::getPhysics() const { return m_Physics; }

void SimpleEntity::setVelocity(Vector2 newVelocity) {
  this->m_Physics.velocity = newVelocity;
}

OrbitalComponent SimpleEntity::getOrbital() const { return m_Orbital; }

void SimpleEntity::setOrbital(OrbitalComponent newOrbital) {
  this->m_Orbital = newOrbital;
}
