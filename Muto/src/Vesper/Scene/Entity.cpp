#include "vzpch.h"
#include "Entity.h"

namespace Vesper {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityID(handle), m_Scene(scene)
	{
	}
}