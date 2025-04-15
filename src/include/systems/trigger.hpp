#pragma once

#include "components/collider.hpp"
#include <common/types.hpp>
#include <core/entity.hpp>
#include <functional>

namespace Systems::Trigger {

using TriggerCallback =
    std::function<void(EntityID triggerID, EntityID activatorID)>;

void Update();
Entity *Register(EntityID triggerID,
                 const std::array<EntityType, MAX_TRIGGER_TYPES> &acceptedTypes,
                 size_t count, TriggerCallback callback);
Entity *
RegisterInteract(EntityID triggerID,
                 const std::array<EntityType, MAX_TRIGGER_TYPES> &acceptedTypes,
                 size_t count, TriggerCallback callback);

} // namespace Systems::Trigger
