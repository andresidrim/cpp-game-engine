#include <components/collider.hpp>
#include <core/entityManager.hpp>
#include <raylib.h>
#include <systems/collision.hpp>
#include <systems/trigger.hpp>

namespace Systems::Trigger {

Entity *Register(EntityID triggerID,
                 const std::array<EntityType, MAX_TRIGGER_TYPES> &acceptedTypes,
                 size_t count, TriggerCallback callback) {
  auto trigger = GlobalEntityManager.GetEntity(triggerID);

  auto triggerCollider = trigger->TryGetComponent<ColliderComponent>();

  if (!trigger || !triggerCollider)
    return nullptr;

  triggerCollider->isTrigger = true;
  triggerCollider->triggered = false;
  triggerCollider->requiresInteraction = false;
  triggerCollider->typeCount =
      count > MAX_TRIGGER_TYPES ? MAX_TRIGGER_TYPES : count;
  triggerCollider->onTrigger = callback;

  for (size_t i = 0; i < triggerCollider->typeCount; i++) {
    triggerCollider->acceptedTypes.at(i) = acceptedTypes.at(i);
  }

  return trigger;
}

Entity *RegisterInteract(EntityID triggerID,
                         const std::array<EntityType, 4> &acceptedTypes,
                         size_t count, TriggerCallback callback) {
  auto trigger = Register(triggerID, acceptedTypes, count, callback);

  auto triggerCollider = trigger->TryGetComponent<ColliderComponent>();

  if (!trigger || !triggerCollider)
    return nullptr;

  triggerCollider->requiresInteraction = true;

  return trigger;
}

void Update() {
  auto &entities = GlobalEntityManager.GetAll();
  size_t count = entities.size();

  for (size_t i = 0; i < count; i++) {
    auto &trigger = entities.at(i);

    if (trigger.IsDestroyed())
      continue;

    auto colliderComponent = trigger.TryGetComponent<ColliderComponent>();

    if (!colliderComponent || !colliderComponent->isTrigger ||
        colliderComponent->triggered ||
        colliderComponent->requiresInteraction && !IsKeyPressed(KEY_E))
      continue;

    for (size_t j = 0; j < count; j++) {
      if (i == j)
        continue;

      auto &other = entities.at(j);

      if (other.IsDestroyed())
        continue;

      auto otherColliderComponent = other.TryGetComponent<ColliderComponent>();

      if (!otherColliderComponent)
        continue;

      if (!Collision::CheckAABB(&trigger, &other))
        continue;

      for (size_t t = 0; t < colliderComponent->typeCount; t++) {
        if (other.GetType() == colliderComponent->acceptedTypes.at(t)) {
          if (colliderComponent->onTrigger) {
            EntityID triggerID = {.index = i, .version = trigger.GetVersion()};
            EntityID activatorID = {.index = j, .version = other.GetVersion()};
            colliderComponent->onTrigger(triggerID, activatorID);
            colliderComponent->triggered = true;
          }

          break;
        }
      }
    }
  }
}

} // namespace Systems::Trigger
