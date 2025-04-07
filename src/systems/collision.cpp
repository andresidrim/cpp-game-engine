#include <cmath>
#include <components/transform.hpp>
#include <core/entityManager.hpp>
#include <external/raymath_operators.hpp>
#include <raylib.h>
#include <systems/collision.hpp>
#include <systems/movement.hpp>

namespace Systems::Collision {

void Update() {
  float dt = GetFrameTime();

  auto &entities = GlobalEntityManager.GetAll();
  const size_t length = entities.size();

  for (size_t i = 0; i < length; i++) {
    auto &a = entities.at(i);

    auto aColliderComponent = a.TryGetComponent<ColliderComponent>();
    if (!aColliderComponent || aColliderComponent->isStatic)
      continue;

    auto aTransformComponent = a.TryGetComponent<TransformComponent>();

    if (!aTransformComponent)
      continue;

    Vector3 originalPos = aTransformComponent->position;
    Vector3 proposedPos = originalPos;

    proposedPos.x += aTransformComponent->velocity.x * dt;
    bool blockedX = false;

    aTransformComponent->position = proposedPos;

    for (size_t j = 0; j < length; j++) {
      if (i == j)
        continue;

      auto &b = entities.at(j);

      auto bColliderComponent = b.TryGetComponent<ColliderComponent>();

      if (!bColliderComponent || bColliderComponent->isTrigger)
        continue;

      auto bTransformComponent = b.TryGetComponent<TransformComponent>();

      if (!bTransformComponent)
        continue;

      if (CheckAABB(&a, &b)) {
        blockedX = true;
        break;
      }
    }

    aTransformComponent->position = originalPos;

    if (blockedX)
      aTransformComponent->velocity.x = 0;

    proposedPos = aTransformComponent->position;
    proposedPos.z += aTransformComponent->velocity.z * dt;
    bool blockedZ = false;

    aTransformComponent->position = proposedPos;

    for (size_t j = 0; j < length; j++) {
      if (i == j)
        continue;

      auto &b = entities.at(j);

      auto bColliderComponent = b.TryGetComponent<ColliderComponent>();

      if (!bColliderComponent || bColliderComponent->isTrigger)
        continue;

      auto bTransformComponent = b.TryGetComponent<TransformComponent>();

      if (!bTransformComponent)
        continue;

      if (CheckAABB(&a, &b)) {
        blockedZ = true;
        break;
      }
    }

    aTransformComponent->position = originalPos;
    if (blockedZ)
      aTransformComponent->velocity.z = 0;

    Systems::Movement::Apply(*aTransformComponent);
  }
}

bool CheckAABB(Entity *a, Entity *b) {
  Vector3 apos = a->GetComponent<TransformComponent>().position;
  Vector3 asize = a->GetComponent<ColliderComponent>().size;

  Vector3 bpos = b->GetComponent<TransformComponent>().position;
  Vector3 bsize = b->GetComponent<ColliderComponent>().size;

  return (fabs(apos.x - bpos.x) * 2 < (asize.x + bsize.x)) &&
         (fabs(apos.y - bpos.y) * 2 < (asize.y + bsize.y)) &&
         (fabs(apos.z - bpos.z) * 2 < (asize.z + bsize.z));
}

bool CheckAABB(const EntityID aID, const EntityID bID) {
  Entity *a = GlobalEntityManager.GetEntity(aID);
  Entity *b = GlobalEntityManager.GetEntity(bID);

  if (!a || !b)
    return false;

  return CheckAABB(a, b);
}

} // namespace Systems::Collision
