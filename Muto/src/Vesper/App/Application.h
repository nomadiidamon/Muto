#pragma once
/// @file Application.h
/// @author Damon S. Green II
/// @brief Controls the run of the Vesper Engine
/// @todo Convert all files/classes in App directory to Vesper::Engine namespace (create it)

#include "../Core/Base.h"
#include "Window.h"
#include "Vesper/App/LayerStack.h"
#include "Vesper/Events/Event.h"
#include "Vesper/Events/ApplicationEvent.h"
#include "Vesper/Core/Timestep.h"
#include "Vesper/ImGui/ImGuiLayer.h"
#include "Vesper/Renderer/RendererAPI.h"


namespace Vesper {


	/// WIP
	struct ApplicationSettings {
		std::string ApplicationName = "Vesper Application";
		std::string WorkingDirectory;
		RendererAPI::API RendererAPI = RendererAPI::API::OpenGL;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		WindowMode Mode = WindowMode::Windowed;
		bool EnableImGui = true;
		bool EnableVSync = false;
	};

	/// @class Application
	/// @brief The core application class that manages the main loop, window, layers, and event handling.
	/// @todo Update class to accept ApplicationSettings in constructor and verify its utility/use
	class Application
	{
	public:

		/// @brief Constructs the Application with the given name.
		///
		/// @param name The name of the application. Defaults to an empty string.
		Application(const std::string& name = "");

		virtual ~Application();

		/// @brief Starts the main application loop.
		///
		/// @todo Add Layer rendering into the main loop
		/// @todo Add separate threads for rendering and updating
		void Run();

		/// @brief Handles incoming events and dispatches them to the appropriate handlers.
		void OnEvent(Event& e);

		/// @brief Adds a layer to the application layer stack.
		void PushLayer(Layer* layer);

		/// @brief Adds an overlay layer to the application layer stack.
		void PushOverlay(Layer* overlay);

		/// @brief Closes the application.
		void Close();

		/// @brief Retrieves the ImGui layer.
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		/// @brief Retrieves the singleton instance of the Application.
		inline static Application& Get() { return *s_Instance; }

		/// @brief Retrieves the application window.
		inline Window& GetWindow() { return *m_Window; }
	private:

		/// @brief Event handler for window close events.
		bool OnWindowClose(WindowCloseEvent& e);
		/// @brief Event handler for window resize events.
		bool OnWindowResize(WindowResizeEvent& e);

		/// @brief Scoped pointer to the applications underlying window.
		Scope<Window> m_Window;
		/// @brief ImGui layer for rendering GUI elements
		ImGuiLayer* m_ImGuiLayer;
		/// @brief Flag indicating whether the application is running.
		bool m_Running = true;
		/// @brief Flag indicating whether the application is minimized.
		bool m_Minimized = false;
		/// @brief Stack of layers managed by the application.
		LayerStack m_LayerStack;
		/// @brief Time of the last frame, used for calculating timestep.
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

