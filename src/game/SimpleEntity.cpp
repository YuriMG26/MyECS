#include "SimpleEntity.h"

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
  std::uniform_real_distribution<float> velx(-10.0f, +10.0f);
  std::uniform_real_distribution<float> vely(-10.0f, +10.0f);
  physics.velocity = {velx(gen), vely(gen)};

  m_IsStar = false;
  m_Position = {position.x, position.y};
  m_Orbital.mass = 10e3;
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
  constexpr float gravitational = 6.6743e-11;
  if (!m_IsStar) {
    if (m_Position.x > GetScreenWidth() || m_Position.x < 0)
      m_Physics.velocity.x *= -1;
    if (m_Position.y > GetScreenHeight() || m_Position.y < 0)
      m_Physics.velocity.y *= -1;

    float radius = Vector2Distance({m_Position.x, m_Position.y},
                                   {m_StarPosition.x, m_StarPosition.y});
    // float velocity = sqrt(2 * (gravitational * m_StarOrbital.mass) /
    // distance); Vector2 m_PositionToAdd;
    float starMass = m_StarOrbital.mass;
    float thisMass = m_Orbital.mass;

    float force = (gravitational * starMass * thisMass) / (radius * radius);

    Vector2 gravityVector = Vector2Subtract(
        {m_StarPosition.x, m_StarPosition.y}, {m_Position.x, m_Position.y});
    gravityVector = Vector2Scale(gravityVector, force * GetFrameTime());

    // TODO: conversion from PositionComponent to Vector2 and vice-versa
    Vector2 finalPosition =
        Vector2Add({m_Position.x, m_Position.y}, gravityVector);
    m_Position.x = finalPosition.x;
    m_Position.y = finalPosition.y;

    m_Position.x += m_Physics.velocity.x * 10.f * GetFrameTime();
    m_Position.y += m_Physics.velocity.y * 10.f * GetFrameTime();
  }
}

void SimpleEntity::draw() {
  // TODO: polymorphism for star
  int size = 3;
  if (m_IsStar) size = 20;
  DrawRectangle(this->m_Position.x, this->m_Position.y, size, size, m_Color);
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
