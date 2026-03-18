#pragma once
/// @file ImGuiLayer.h
/// @author Damon S. Green II
/// @brief Defines the ImGuiLayer class, which is responsible for rendering the ImGui interface. Derives from the Layer class.

#include "Vesper/Core/Base.h"
#include "Vesper/Events/Event.h"
#include "Vesper/Events/ApplicationEvent.h"
#include "Vesper/Events/KeyEvent.h"
#include "Vesper/Events/MouseEvent.h"
#include "Vesper/App/Layer.h"

namespace Vesper {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		virtual void Begin();
		virtual void End();

		virtual void SetBlockEvents(bool block) { m_BlockEvents = block; }
		virtual void SetDarkThemeColors();
	protected:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}

