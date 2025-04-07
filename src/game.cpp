#include "common/types.hpp"
#include "components/collider.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "systems/render.hpp"
#include <core/entity.hpp>
#include <core/entityManager.hpp>
#include <game.hpp>
#include <raylib.h>

static Camera3D camera;

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

  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
}

void UpdateGame() {
  GlobalEntityManager.UpdateAll();

  BeginDrawing();
  ClearBackground(DARKGRAY);

  BeginMode3D(camera);
  Systems::Render::DrawAll();
  EndMode3D();

  EndDrawing();
}
