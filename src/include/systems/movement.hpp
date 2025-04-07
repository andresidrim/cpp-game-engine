#pragma once

#include "components/transform.hpp"

namespace Systems::Movement {

void Update(TransformComponent &transform);
void Apply(TransformComponent &transform);

} // namespace Systems::Movement
