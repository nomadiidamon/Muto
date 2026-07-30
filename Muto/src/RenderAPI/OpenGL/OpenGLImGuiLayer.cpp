#include "mupch.h"
#include "OpenGLImGuiLayer.h"
#include "GUI/ImGui/ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "App/Application.h"
#include "App/Layer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ImGuizmo.h"


namespace Muto {
	OpenGLImGuiLayer::OpenGLImGuiLayer() : ImGuiLayer()
	{
	}

	OpenGLImGuiLayer::~OpenGLImGuiLayer()
	{
	}

	void OpenGLImGuiLayer::OnAttach()
	{
		ImGuiLayer::OnAttach();



	}

	void OpenGLImGuiLayer::OnDetach()
	{
		ImGuiLayer::OnDetach();



	}

	void OpenGLImGuiLayer::OnImGuiRender()
	{
		ImGuiLayer::OnImGuiRender();


	}

	void OpenGLImGuiLayer::OnEvent(Event& e)
	{
		ImGuiLayer::OnEvent(e);


	}

	void OpenGLImGuiLayer::Begin()
	{
		ImGuiLayer::Begin();
	}

	void OpenGLImGuiLayer::End()
	{
		ImGuiLayer::End();
	}

	void OpenGLImGuiLayer::SetDarkThemeColors()
	{
		ImGuiLayer::SetDarkThemeColors();
	}

}