#pragma once
#include "Vesper/Core/Base.h"
#include "Vesper/Core/Log.h"
#include "Vesper/Scene/Scene.h"
#include "Vesper/Scene/Entity.h"

#include "Vesper/Renderer/Framebuffer.h"

namespace Vesper {

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