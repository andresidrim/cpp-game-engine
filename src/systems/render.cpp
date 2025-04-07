#include <core/entityManager.hpp>
#include <raylib.h>
#include <systems/render.hpp>

namespace Systems::Render {

void DrawAll() {
  auto &entities = GlobalEntityManager.GetAll();

  for (size_t i = 0; i < entities.size(); i++) {
    auto &e = entities.at(i);

    auto transformComponent = e.TryGetComponent<TransformComponent>();
    auto renderableComponent = e.TryGetComponent<RenderableComponent>();

    if (!transformComponent || !renderableComponent)
      continue;

    DrawCube(transformComponent->position, renderableComponent->size.x,
             renderableComponent->size.y, renderableComponent->size.z,
             renderableComponent->color);
  }
}

} // namespace Systems::Render
