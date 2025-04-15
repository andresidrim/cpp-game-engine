#pragma once

#include "core/entity.hpp"
#define MAX_CAMERAS 16

namespace Systems::Camera {

enum class CameraBehavior { Follow, Fixed };

struct CameraConfig {
  CameraBehavior behavior = CameraBehavior::Follow;

  EntityID followTargetID{};
  Vector3 offset{};

  float followLerp = 10.0f;
  float rotationIntensity = 1.0f;
  float zoom = 45.0f;

  Rectangle boundsXZ{};
  int priority = 0;
};

struct CameraWrapper {
  Camera3D cam{};
  CameraConfig config{};
  bool active = false;
  float yaw = 0.0f;
  float pitch = 0.0f;
};

} // namespace Systems::Camera
