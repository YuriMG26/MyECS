#pragma once

#include <string>

#include "../../vendor/raylib/include/raylib.h"

struct TransformComponent {
  Vector2 position;
  float rotation;
  float scale;
};

struct TextureComponent {
  Texture2D texture;
  char path[64];
};

struct TagComponent {
  std::string tag;
};

struct ParticleTag {
  Color color;
};

struct PhysicsComponent {
  Vector2 velocity;
};
