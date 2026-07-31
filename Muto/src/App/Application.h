#pragma once
/// @file Application.h
/// @author Damon S. Green II
/// @brief Controls the run of the Muto Engine
/// @todo Convert all files/classes in App directory to Muto::Engine namespace (create it)

#include "../Core/Base.h"
#include "Gateware.h"
#include "Window.h"
#include "App/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Core/Timestep.h"
#include "GUI/ImGui/ImGuiLayer.h"
#include "Renderer/RendererAPI.h"


namespace Muto {

	/// @enum PathResolveMode
	/// @brief Specifies the mode for resolving resource paths in the application.
	enum class PathResolveMode {
		WorkingDirectory,
		ProjectDirectory,
		AssetsDirectory
	};

	/// @struct ApplicationSettings
	/// @brief Holds configuration settings for the application.
	struct ApplicationSettings {
		/// @brief The name of the application.
		std::string ApplicationName = "Muto Application";
		
		/// @brief The working directory of the application.
		std::string WorkingDirectory;
		
		/// @brief The project directory of the application.
		std::string ProjectDirectory;
		
		/// @brief The assets directory of the application.
		std::string AssetsDirectory;
		
		/// @brief The renderer API to use for the application.
		RendererAPI::API RendererAPI = RendererAPI::API::OpenGL;
		
		/// @brief The width of the application window.
		uint32_t Width = 1280;

		/// @brief The height of the application window.
		uint32_t Height = 720;

		/// @brief The window mode of the application (e.g., windowed, fullscreen, borderless).
		WindowMode Mode = WindowMode::Windowed;

		/// @brief Flag indicating whether ImGui is enabled for the application.
		bool EnableImGui = true;

		/// @brief Flag indicating whether vertical synchronization (VSync) is enabled for the application.
		bool EnableVSync = false;

		/// @brief The file system interface for the application.
		GW::SYSTEM::GFile FileSystem;
	};

	/// @class Application
	/// @brief The core application class that manages the main loop, window, layers, and event handling.
	/// @todo Update class to accept ApplicationSettings in constructor and verify its utility/use
	/// @todo Create a dedicated ResourceManager class to handle resource path resolution and management
	class Application
	{
	public:

		/// @brief Constructs the Application with the given name.
		///
		/// @param name The name of the application. Defaults to an empty string.
		Application(const std::string& name = "");
		
		/// @brief Constructs the Application with the given settings.
		///
		/// @param settings The settings to configure the application.
		Application(ApplicationSettings settings);

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

		/// @brief Retrieves the application settings.
		inline ApplicationSettings& GetSettings() { return *m_Settings; }

		/// @brief Retrieves the application settings as a const reference.
		inline const ApplicationSettings& GetSettings() const { return *m_Settings; }

		/// @brief Resolves the full path to a resource based on a relative path and the application's settings.
		///
		/// @param Path The path to the resource.
		/// @param Mode The mode to use for resolving the path. Defaults to PathResolveMode::AssetsDirectory.
		std::string ResolvePath(const std::string& Path, PathResolveMode Mode = PathResolveMode::AssetsDirectory) const;

	private:
		/// @brief Event handler for window close events.
		bool OnWindowClose(WindowCloseEvent& e);
		/// @brief Event handler for window resize events.
		bool OnWindowResize(WindowResizeEvent& e);

		/// @brief Resolves the full path to a resource based on the application's working directory.
		///
		/// @param Path The path to the resource.
		std::string ResolvePath_WorkingDirectory(const std::string& Path) const;

		/// @brief Resolves the full path to a resource based on the application's project directory.
		///
		/// @param Path The path to the resource.
		std::string ResolvePath_ProjectDirectory(const std::string& Path) const;

		/// @brief Resolves the full path to a resource based on the application's assets directory.
		///
		/// @param Path The path to the resource.
		std::string ResolvePath_AssetsDirectory(const std::string& Path) const;


		/// @brief Initializes the file system for the application.
		MutoResult InitFileSystem();

		///	@brief Initializes the file system for the application with the given settings.
		///
		/// @param Settings The settings to configure the file system.
		MutoResult InitFileSystem(ApplicationSettings& Settings);

	private:
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

		/// @brief Scoped pointer to the application settings.
		Scope<ApplicationSettings> m_Settings;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

