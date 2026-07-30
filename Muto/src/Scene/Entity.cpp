#include "mupch.h"
#include "Entity.h"

namespace Muto {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityID(handle), m_Scene(scene)
	{
	}
}