#include "common/types.hpp"
#include "components/collider.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "systems/camera.hpp"
#include "systems/render.hpp"
#include <core/entity.hpp>
#include <core/entityManager.hpp>
#include <game.hpp>
#include <raylib.h>
#include <systems/cameraManager.hpp>

void InitGame() {
  EntityID playerID = GlobalEntityManager.CreateEntity(
      EntityType::Player, EntityTag::Player,
      TransformComponent{.position = {0, 0, 0}, .speed = 5.0f},
      ColliderComponent{.size = {2, 2, 2}},
      RenderableComponent{.color = RED, .size = {2, 2, 2}});

  EntityID wallID = GlobalEntityManager.CreateEntity(
      EntityType::Object, EntityTag::None,
      TransformComponent{.position = {3, 0, 0}},
      ColliderComponent{.size = {2, 2, 2}, .isStatic = true},
      RenderableComponent{.color = BLUE, .size = {2, 2, 2}});

  int followCamId =
      GlobalCameraManager.CreateCamera(Systems::Camera::CameraConfig{
          .behavior = Systems::Camera::CameraBehavior::Follow,
          .followTargetID = playerID,
          .offset = {0, 6, 10},
          .followLerp = 5.0f,
          .rotationIntensity = 0.0f,
          .zoom = 45.0f,
          .boundsXZ = (Rectangle){0}, // ok por enquanto
          .priority = 10});
  GlobalCameraManager.SetActiveCamera(followCamId);

  int fixedCamId =
      GlobalCameraManager.CreateCamera(Systems::Camera::CameraConfig{
          .behavior = Systems::Camera::CameraBehavior::Fixed,
          .followTargetID = playerID,
          .offset = {10, 6, -8},
          .followLerp = 10.0f,
          .rotationIntensity = 5.0f,
          .zoom = 50.0f,
          .boundsXZ = {4, -4, 8, 8},
          .priority = 20});

  DisableCursor();
}

void UpdateGame() {
  GlobalEntityManager.UpdateAll();
  GlobalCameraManager.Update(0.0005f, 0.0005f / 2.0f);

  BeginDrawing();
  ClearBackground(DARKGRAY);

  BeginMode3D(*GlobalCameraManager.GetActiveCamera());
  Systems::Render::DrawAll();
  EndMode3D();

  EndDrawing();
}
