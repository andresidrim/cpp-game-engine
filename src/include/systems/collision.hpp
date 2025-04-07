#pragma once

#include "core/entity.hpp"

namespace Systems::Collision {

void Update();
bool CheckAABB(const EntityID aID, const EntityID bID);
bool CheckAABB(Entity *a, Entity *b);

} // namespace Systems::Collision
