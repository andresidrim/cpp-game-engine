#pragma once

#include "../common/types.hpp"
#include <array>
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

  std::array<EntityType, MAX_TRIGGER_TYPES> acceptedTypes;
  size_t typeCount;

  std::function<void(EntityID triggerID, EntityID activatorID)> onTrigger;
};
