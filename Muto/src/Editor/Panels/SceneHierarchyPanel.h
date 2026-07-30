#pragma once
#include "Core/Base.h"
#include "Core/Log.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

#include "Renderer/Framebuffer.h"

namespace Muto {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
		Ref<Framebuffer> m_Framebuffer;

	};

}