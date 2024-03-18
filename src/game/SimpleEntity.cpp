#include "SimpleEntity.h"

void SimpleEntity::makeStar() {
  m_Color = {0, 255, 255, 255};
  m_Position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
  m_Physics.velocity = {0, 0};
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
  std::uniform_real_distribution<float> velx(-10.0f, +10.0f);
  std::uniform_real_distribution<float> vely(-10.0f, +10.0f);
  physics.velocity = {velx(gen), vely(gen)};

  m_Position = {position.x, position.y};
  m_Physics = physics;
  m_Color = color;
}

SimpleEntity::SimpleEntity(bool isStar) {
  if (isStar) {
    makeStar();
  } else {
    makePlanet();
  }
}

SimpleEntity::~SimpleEntity() {}

void SimpleEntity::update(float delta) {
  this->m_Position.x += this->m_Physics.velocity.x * 10.f * delta;
  this->m_Position.y += this->m_Physics.velocity.y * 10.f * delta;

  if (m_Position.x < 0 or m_Position.x + 20 > GetScreenWidth()) {
    m_Physics.velocity.x *= -1.0f;
  }

  if (m_Position.y < 0 or m_Position.y + 20 > GetScreenHeight()) {
    m_Physics.velocity.y *= -1.0f;
  }
}

void SimpleEntity::draw() {
  DrawRectangle(this->m_Position.x, this->m_Position.y, 3, 3, m_Color);
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
