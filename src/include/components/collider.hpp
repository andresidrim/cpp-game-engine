#pragma once

#include "../common/types.hpp"
#include <cstddef>
#include <functional>
#include <raylib.h>

#define MAX_TRIGGER_TYPES 4

struct ColliderComponent {
  Vector3 size;
  bool isStatic;
  bool isTrigger;
  bool triggered;
  bool requiresInteraction;

  EntityType acceptedTypes[MAX_TRIGGER_TYPES];
  size_t typeCount;

  std::function<void(EntityID triggerID, EntityID activatorID)> onTrigger;
};
