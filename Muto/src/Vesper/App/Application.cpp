#include "vzpch.h"
#include "Application.h"
#include "Vesper/Renderer/Renderer.h"
#include "Vesper/Input/Input.h"

/// @file Application.cpp
/// @author Damon S. Green II
/// @brief Implementation of the Application class for the Vesper engine.
/// @todo Remove include GLFW for time function, replace with Platform later
#include <GLFW/glfw3.h>

namespace Vesper {


	Application* Application::s_Instance = nullptr;


	Application::Application(const std::string& name)
	{
		VZ_PROFILE_FUNCTION();

		VZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);


		Renderer::Init();


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		VZ_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		VZ_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		VZ_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}

	}

	/// @todo split the Run function into separate functions for update and render, and add a thread for each
	void Application::Run()
	{
		VZ_PROFILE_FUNCTION();
		while (m_Running)
		{
			VZ_PROFILE_SCOPE("RunLoop");
			/// @todo Platform::GetTime()
			float time = (float)glfwGetTime(); 
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				VZ_PROFILE_SCOPE("LayerStack OnUpdate");

				/// @todo Sort layers

				/// Update layers
				for (auto layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
				VZ_PROFILE_SCOPE("ImGuiLayer OnImGuiRender");
				m_ImGuiLayer->Begin();
				/// ImGui render layers
				for (auto layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			/// @todo Add a Layer render function and call it here for all Layers

			{
				VZ_PROFILE_SCOPE("Window OnUpdate");
				/// Update window second
				m_Window->OnUpdate();
			}
		};
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		VZ_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		VZ_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}