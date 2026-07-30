#pragma once

#include "Core/Base.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "App/Layer.h"
#include "GUI/ImGui/ImGuiLayer.h"

namespace Muto {

	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		OpenGLImGuiLayer();
		~OpenGLImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void SetBlockEvents(bool block) { m_BlockEvents = block; }
		virtual void SetDarkThemeColors() override;

	};

}

