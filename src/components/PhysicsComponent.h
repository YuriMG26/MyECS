#pragma once

#include "../../vendor/raylib/include/raylib.h"
#include "../../vendor/raylib/include/raymath.h"

struct PhysicsComponent {
  Vector2 velocity;
  Rectangle bounds;
};
