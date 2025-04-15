#include "systems/cameraManager.hpp"
#include <cmath>
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

  float dt = GetFrameTime();

  if (Vector3Length(inputDirection) > 0.0f) {
    inputDirection = Vector3Normalize(inputDirection);

    // Aplica a rotação da câmera ao input para obter movimento relativo à
    // câmera
  }

  float yaw = GlobalCameraManager.GetActiveCameraWrapper()->yaw;
  float sinYaw = sinf(yaw);
  float cosYaw = cosf(yaw);

  Vector3 worldDir = {inputDirection.x * cosYaw - inputDirection.z * sinYaw,
                      0.0f,
                      inputDirection.x * sinYaw + inputDirection.z * cosYaw};

  worldDir = Vector3Normalize(worldDir);

  // Movimento
  float acceleration = 20.0f;
  transform.velocity.x = Lerp(transform.velocity.x,
                              worldDir.x * transform.speed, acceleration * dt);
  transform.velocity.z = Lerp(transform.velocity.z,
                              worldDir.z * transform.speed, acceleration * dt);

  // Atualiza a rotação do jogador para olhar na direção do movimento
  float desiredYaw = atan2f(worldDir.x, worldDir.z);
  float turnSpeed = 12.0f;
  transform.rotation.y = Lerp(transform.rotation.y, desiredYaw, turnSpeed * dt);
}

/*float acceleration = 20.0f;*/
/*transform.velocity.x = Lerp(transform.velocity.x,*/
/*                            worldDir.x * transform.speed, acceleration *
 * dt);*/
/*transform.velocity.z = Lerp(transform.velocity.z,*/
/*                            worldDir.z * transform.speed, acceleration *
 * dt);*/

void Apply(TransformComponent &transform) {
  float dt = GetFrameTime();

  transform.position.x += transform.velocity.x * dt;
  transform.position.z += transform.velocity.z * dt;
}

} // namespace Systems::Movement
