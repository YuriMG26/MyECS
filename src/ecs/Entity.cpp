#include "Entity.h"

Entity::Entity(entt::entity handle, Scene *scenePointer)
    : m_Entity(handle), m_Scene(scenePointer) {}
