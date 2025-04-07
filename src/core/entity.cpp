#include "common/types.hpp"
#include <core/entity.hpp>
#include <cstdint>

void Entity::ClearComponents() { components.Clear(); }

bool Entity::IsDestroyed() const { return destroyed; }

void Entity::MarkDestroyed() { destroyed = true; }

uint32_t Entity::GetVersion() const { return version; }

void Entity::UpdateVersion(uint32_t increment) { version += increment; }

void Entity::SetVersion(uint32_t version) { this->version = version; }

EntityType Entity::GetType() const { return type; }

void Entity::SetType(EntityType type) { this->type = type; }

EntityTag Entity::GetTag() const { return tag; }

void Entity::SetTag(EntityTag tag) { this->tag = tag; }

std::string Entity::GetTypeName() {
  switch (type) {
  case EntityType::Player:
    return "Player";
  case EntityType::Enemy:
    return "Enemy";
  case EntityType::Object:
    return "Object";
  default:
    return "Unknown";
  }
}
