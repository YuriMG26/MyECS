#pragma once

#include <cstdint>

class GameObject {
 public:
  GameObject();
  ~GameObject();

  virtual void update(float delta) = 0;
  virtual void draw() = 0;

 protected:
};