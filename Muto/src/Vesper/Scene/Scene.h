#pragma once
/// @file Scene.h
/// @author Damon S. Green II
/// @brief Defines the Scene class, which represents a scene in the application and manages entities and their components.
/// @note The Scene class provides methods for creating and destroying entities, updating the scene during runtime and editor modes, and handling viewport resizing.

#include <entt.hpp>
#include "Components.h"
#include "Vesper/Core/Timestep.h"


namespace Vesper {

	class Entity;
	class EditorCamera;

	/// @class Scene
	/// @brief Represents a scene in the application and manages entities and their components.
	/// @todo Create a friend class SceneRenderer;
	class Scene
	{
	public:
		Scene();
		Scene(const std::string& name);
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntity(const std::string& name, const std::string& uuid);
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		std::string m_Name;
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 160, m_ViewportHeight = 90;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
		friend class SceneCamera;
		// friend class SceneRenderer;

		void SetName(const std::string& name) { m_Name = name; }
		const std::string& GetName() const { return m_Name; }
	};


}