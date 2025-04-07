#pragma once

enum class EntityType { Player, Enemy, Object };

enum class EntityTag {
  None = 0,
  Player,
  Enemy,
  Item,
  Door,
  UI
  /**/
};

/*enum class ComponentFlags {*/
/*  None = 0,*/
/*  Transform = 1 << 0,*/
/*  Renderable = 1 << 1,*/
/*  Collider = 1 << 2,*/
/*};*/

struct EntityID;
class Entity;
class EntityManager;
struct TransformComponent;
struct ColliderComponent;
struct RenderableComponent;
