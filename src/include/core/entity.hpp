#pragma once

#include <common/types.hpp>
#include <components/collider.hpp>
#include <components/component_storage.hpp>
#include <components/renderable.hpp>
#include <components/transform.hpp>
#include <cstdint>
#include <string>

#define MAX_ENTITIES 1000

struct EntityID {
  size_t index;
  uint32_t version;
};

class Entity {
  friend class EntityManager;

public:
  template <typename T> void AddComponent(const T &component) {
    components.Add<T>(component);
  }

  template <typename... Components>
  void AddComponents(const Components &...components) {
    (AddComponent(components), ...);
  }

  template <typename T> bool HasComponent() const {
    return components.Has<T>();
  }

  template <typename T> T &GetComponent() const { return components.Get<T>(); }

  template <typename T> T *TryGetComponent() const {
    return this->HasComponent<T>() ? &this->GetComponent<T>() : nullptr;
  }

  template <typename T> void RemoveComponent() { components.Remove<T>(); }

  void ClearComponents();

  bool IsDestroyed() const;
  void MarkDestroyed();

  uint32_t GetVersion() const;
  void UpdateVersion(uint32_t increment = 1);
  void SetVersion(uint32_t version);

  EntityType GetType() const;
  void SetType(EntityType type);

  EntityTag GetTag() const;
  void SetTag(EntityTag tag);

  std::string GetTypeName();

private:
  /* Direct usage of variables and constructor is not recommended */
  ComponentStorage components;

  bool destroyed;
  uint32_t version;

  EntityType type;
  EntityTag tag;

  template <typename... Components>
  Entity(EntityType type, EntityTag tag, const Components &...comps)
      : destroyed(false), version(0), type(type), tag(tag) {
    AddComponents(comps...);
  }
};
