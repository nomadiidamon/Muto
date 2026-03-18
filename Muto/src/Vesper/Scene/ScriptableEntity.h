#pragma once
/// @file ScriptableEntity.h
/// @author Damon S. Green II
/// @brief Defines the ScriptableEntity class, which serves as a base for scriptable entities in a scene.

#include "Entity.h"

namespace Vesper {

	/// @brief Base class for scriptable entities within a scene.
	///
	/// A ScriptableEntity allows for custom behavior to be defined for entities in a scene, not already provided as standardized components.
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {};

		/// @brief Retrieves a reference to a component of type T attached to the entity.
		///
		/// @tparam T The type of the component to retrieve.
		/// @return Reference to the component of type T.
		/// Will assert if the component does not exist.
		template<typename T>
		T& GetComponent() 
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		/// @brief Sets the entity associated with this scriptable entity.
		///
		/// Meant for internal use by the Scene class.
		/// Should be overridden in derived classes if additional setup is required when the entity is set.
		virtual void OnCreate() {}

		/// @brief Called when the entity is destroyed.
		///
		/// Meant for internal use by the Scene class.
		/// Should be overridden in derived classes to handle cleanup.
		virtual void OnDestroy() {}

		/// @brief Called every frame to update the entity.
		///
		/// @param ts The timestep representing the time elapsed since the last update.
		/// Custom behavior should be implemented here in derived classes.
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}