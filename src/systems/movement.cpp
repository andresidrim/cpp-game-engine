#include <raylib.h>
#include <raymath.h>
#include <systems/movement.hpp>

namespace Systems::Movement {

void Update(TransformComponent &transform) {
  Vector3 inputDirection = {0};

  if (IsKeyDown(KEY_W))
    inputDirection.z -= 1;
  if (IsKeyDown(KEY_S))
    inputDirection.z += 1;
  if (IsKeyDown(KEY_A))
    inputDirection.x -= 1;
  if (IsKeyDown(KEY_D))
    inputDirection.x += 1;

  if (Vector3Length(inputDirection) > 0.0f)
    inputDirection = Vector3Normalize(inputDirection);

  float dt = GetFrameTime();

  float acceleration = 20.0f;

  transform.velocity.x =
      Lerp(transform.velocity.x, inputDirection.x * transform.speed,
           acceleration * dt);

  transform.velocity.z =
      Lerp(transform.velocity.z, inputDirection.z * transform.speed,
           acceleration * dt);
}

void Apply(TransformComponent &transform) {
  float dt = GetFrameTime();

  transform.position.x += transform.velocity.x * dt;
  transform.position.z += transform.velocity.z * dt;
}

} // namespace Systems::Movement
