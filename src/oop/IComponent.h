#pragma once

#include "../../vendor/raylib/include/raylib.h"
#include "../../vendor/raylib/include/raymath.h"

class IComponent
{
public:
  virtual void update(float delta) = 0;
};
