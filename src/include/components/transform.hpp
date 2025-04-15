#pragma once

#include <raylib.h>

struct TransformComponent {
  Vector3 position;
  Vector3 rotation;
  Vector3 velocity;
  float speed;
};
