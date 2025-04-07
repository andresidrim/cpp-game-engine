#pragma once

#include "common/types.hpp"
#include "entity.hpp"
#include <cstdint>
#include <vector>

class EntityManager {
public:
  EntityManager();

  template <typename... Components>
  EntityID CreateEntity(EntityType type = EntityType::Object,
                        EntityTag tag = EntityTag::None,
                        const Components &...components) {
    {
      Entity entity(type, tag, components...);

      size_t index;
      if (!freeIndices.empty()) {
        index = freeIndices.back();
        freeIndices.pop_back();
        entity.UpdateVersion(++versions[index]);
        entities[index] = std::move(entity);
      } else {
        index = entities.size();
        entity.UpdateVersion(++versionCounter);
        versions.push_back(entity.GetVersion());
        entities.push_back(std::move(entity));
      }

      return EntityID{index, entities[index].GetVersion()};
    }
  }

  Entity *GetEntity(EntityID id);
  void DestroyEntity(EntityID id);
  void CleanupDestroyedEntities();

  std::vector<Entity> &GetAll();
  size_t GetEntityCount() const;

  void UpdateAll();

private:
  std::vector<Entity> entities;
  std::vector<size_t> freeIndices;
  std::vector<uint32_t> versions;
  uint32_t versionCounter = 0;
};

extern EntityManager GlobalEntityManager;
