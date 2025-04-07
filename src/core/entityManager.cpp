#include "components/transform.hpp"
#include "core/entity.hpp"
#include "systems/collision.hpp"
#include "systems/movement.hpp"
#include <core/entityManager.hpp>

EntityManager::EntityManager() {
  entities.reserve(MAX_ENTITIES);
  versions.resize(MAX_ENTITIES, 0);
}

Entity *EntityManager::GetEntity(EntityID id) {
  if (id.index >= entities.size())
    return nullptr;

  Entity &e = entities[id.index];
  if (e.IsDestroyed() || e.GetVersion() != id.version)
    return nullptr;

  return &e;
}

void EntityManager::DestroyEntity(EntityID id) {
  if (Entity *e = GetEntity(id)) {
    e->MarkDestroyed();
  }
}

void EntityManager::CleanupDestroyedEntities() {
  for (size_t i = 0; i < entities.size(); i++) {
    if (entities.at(i).IsDestroyed()) {
      size_t last = entities.size();

      if (i != last) {
        entities.at(i) = std::move(entities[last]);
        versions.at(i) = versions[last];
      }

      entities.pop_back();
      freeIndices.push_back(i);
    } else {
      ++i;
    }
  }
}

std::vector<Entity> &EntityManager::GetAll() { return entities; }

size_t EntityManager::GetEntityCount() const { return entities.size(); }

void EntityManager::UpdateAll() {
  auto &entities = GetAll();

  for (size_t i = 0; i < entities.size(); i++) {
    auto &e = entities.at(i);

    if (e.IsDestroyed())
      continue;

    /* Handle entity related systems */
    if (e.HasComponent<TransformComponent>()) {
      auto &transformComponent = e.GetComponent<TransformComponent>();

      Systems::Movement::Update(transformComponent);
    }
  }

  Systems::Collision::Update();

  CleanupDestroyedEntities();
}

EntityManager GlobalEntityManager;
