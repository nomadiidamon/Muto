#pragma once
/// @file Entity.h
/// @author Damon S. Green II
/// @brief Defines the Entity class, which represents an entity in a scene and provides methods to manipulate its components.

#include "entt.hpp"

#include "Scene.h"

namespace Vesper {

	/// @class Entity
	/// @brief Represents an entity in a scene.
	/// 
	/// Contains a handle to an entity (entt::entity) in a scene and provides methods to manipulate its components.
	class Entity
	{
	public:
		Entity() = default;

		/// @brief Constructs an Entity with the given handle and scene.
		///
		/// @param handle The handle to the entity.
		/// @param scene The scene to which the entity belongs.
		Entity(entt::entity handle, Scene* scene);

		/// @brief Copy constructor for Entity.
		Entity(const Entity& other) = default;


		/// Checks if the entity has a component of type T.
		/// 
		/// @tparam T The type of component to check for.
		/// @return true if the entity has the component, false otherwise.
		template<typename T>
		bool HasComponent() const 
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
		}

		/// Adds a component of type T to the entity with the provided arguments Otherwise, asserts if the entity already has the component.
		/// 
		/// @tparam T The type of component to add.
		/// @tparam Args The types of arguments to forward to the component's constructor.
		/// @param args The arguments to forward to the component's constructor.
		/// @return A reference to the newly added component.
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			VZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		/// Adds or replaces a component of type T to the entity with the provided arguments.
		/// 
		/// @tparam T The type of component to add or replace.
		/// @tparam Args The types of arguments to forward to the component's constructor.
		/// @param args The arguments to forward to the component's constructor.
		/// @return A reference to the newly added or replaced component.
		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace_or_replace<T>(m_EntityID, std::forward<Args>(args)...);
		}

		/// Retrieves a reference to the component of type T attached to the entity if it exists. Otherwise, asserts.
		/// 
		/// @tparam T The type of component to retrieve.
		/// @return A reference to the component.
		template<typename T>
		T& GetComponent() 
		{
			VZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		/// Retrieves a reference to the component of type T attached to the entity if it exists. Otherwise, adds the component with the provided arguments and returns it.
		/// 
		/// @tparam T The type of component to add.
		/// @tparam Args The types of arguments to forward to the component's constructor.
		/// @param args The arguments to forward to the component's constructor.
		/// @return A reference to the newly added component.
		template<typename T, typename... Args>
		T& GetOrAddComponent(Args&&... args)
		{
			if (HasComponent<T>())
				return GetComponent<T>();
			else
				return AddComponent<T>(std::forward<Args>(args)...);
		}
	
		/// Removes the component of type T from the entity if it exists. Otherwise, asserts.
		/// 
		/// @tparam T The type of component to remove.
		template<typename T>
		void RemoveComponent() 
		{
			VZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		/// Retrieves a const reference to the UUID of the entity.
		/// 
		/// @return A const reference to the UUID of the entity.
		const UUID& GetID() 
		{
			return GetComponent<UUIDComponent>().ID;
		}

		/// Retrieves a const reference to the name of the entity.
		/// 
		/// @return A const reference to the name of the entity.	
		const std::string& GetName() 
		{
			return GetComponent<NameComponent>().Name;
		}


		operator bool() const { return m_EntityID != entt::null; }
		operator entt::entity() const { return m_EntityID; }
		operator uint32_t() const { return (uint32_t)m_EntityID; }
		bool operator==(const Entity& other) const {	return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;	}
		bool operator!=(const Entity& other) const {	return !(*this == other);	}

	private:
		/// @brief The unique identifier of the entity within the scene.
		entt::entity m_EntityID {entt::null};
		/// @brief Pointer to the scene that contains the entity.
		Scene* m_Scene = nullptr;
	};


}