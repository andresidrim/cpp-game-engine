#include "components/renderable.hpp"
#include "components/transform.hpp"
#include <core/entityManager.hpp>
#include <raylib.h>
#include <rlgl.h>
#include <systems/render.hpp>

namespace Systems::Render {

void DrawAll() {
  auto &entities = GlobalEntityManager.GetAll();

  for (size_t i = 0; i < entities.size(); i++) {
    auto &e = entities.at(i);

    if (!e.HasComponent<TransformComponent>() ||
        !e.HasComponent<RenderableComponent>())
      continue;

    auto &transformComponent = e.GetComponent<TransformComponent>();
    auto &renderableComponent = e.GetComponent<RenderableComponent>();

    rlPushMatrix();

    rlTranslatef(transformComponent.position.x, transformComponent.position.y,
                 transformComponent.position.z);

    rlRotatef(RAD2DEG * transformComponent.rotation.y, 0, 1, 0);

    DrawCube((Vector3){0, 0, 0}, renderableComponent.size.x,
             renderableComponent.size.y, renderableComponent.size.z,
             renderableComponent.color);

    rlPopMatrix();
  }
}

} // namespace Systems::Render
