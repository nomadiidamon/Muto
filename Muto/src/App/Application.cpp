#include "mupch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"

/// @file Application.cpp
/// @author Damon S. Green II
/// @brief Implementation of the Application class for the Vesper engine.
/// @todo Remove include GLFW for time function, replace with Platform later
#include <GLFW/glfw3.h>

namespace Muto {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		MU_PROFILE_FUNCTION();
		MU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Settings = CreateScope<ApplicationSettings>(ApplicationSettings());
		m_Settings->ApplicationName = name;
		m_Settings->Width = m_Window->GetWidth();
		m_Settings->Height = m_Window->GetHeight();

		MutoResult result = InitFileSystem();
		if (!result.IsSuccess())
		{
			MU_CORE_ERROR("Application::InitFileSystem() was not successful. Message: {0}", result.ResultMessage);
			MU_CORE_ASSERT(false, result.ReturnError());
		}

		// Init the renderer at the end to ensure pathing has been setup correctly for any resources that may be needed during initialization.
		Renderer::Init();
	}

	Application::Application(ApplicationSettings settings)
	{
		MU_PROFILE_FUNCTION();
		MU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(settings.ApplicationName, settings.Width, settings.Height));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(settings.EnableVSync);

		m_Settings = CreateScope<ApplicationSettings>(settings);
		if (m_Settings->RendererAPI == RendererAPI::API::None)
		{
			m_Settings->EnableImGui = false;
			MU_CORE_WARN("RendererAPI is set to None, disabling ImGui.");
		}
		if (m_Settings->EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
		else
		{
			m_ImGuiLayer = nullptr;
		}

		MutoResult result = InitFileSystem(*m_Settings);
		if (!result.IsSuccess())
		{
			MU_CORE_ERROR("Application::InitFileSystem( *m_Settings ) was not successful. Message: {0}", result.ResultMessage);
			MU_CORE_ASSERT(false, result.ReturnError());
		}

		// Init the renderer at the end to ensure pathing has been setup correctly for any resources that may be needed during initialization.
		Renderer::Init();
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		MU_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		MU_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		MU_PROFILE_FUNCTION();
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
		MU_PROFILE_FUNCTION();
		while (m_Running)
		{
			MU_PROFILE_SCOPE("RunLoop");
			/// @todo Platform::GetTime()
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				MU_PROFILE_SCOPE("LayerStack OnUpdate");

				/// @todo Sort layers

				/// Update layers
				for (auto layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
				MU_PROFILE_SCOPE("ImGuiLayer OnImGuiRender");
				m_ImGuiLayer->Begin();
				/// ImGui render layers
				for (auto layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			/// @todo Add a Layer render function and call it here for all Layers

			{
				MU_PROFILE_SCOPE("Window OnUpdate");
				/// Update window second
				m_Window->OnUpdate();
			}
		};
	}

	std::string Application::ResolvePath(const std::string& path, PathResolveMode mode) const
	{
		if (path.empty())
		{
			MU_CORE_WARN("ResolvePath called with empty path.");
			return std::string();
		}

		std::string resolvedPath;
		switch (mode)
		{
			case PathResolveMode::WorkingDirectory:
				resolvedPath = ResolvePath_WorkingDirectory(path);
				break;
			case PathResolveMode::ProjectDirectory:
				resolvedPath = ResolvePath_ProjectDirectory(path);
				break;
			case PathResolveMode::AssetsDirectory:
				resolvedPath = ResolvePath_AssetsDirectory(path);
				break;
			default:
				MU_CORE_WARN("ResolvePath called with unknown PathResolveMode.");
				resolvedPath = std::string();
				break;
		}
		return resolvedPath;
	}

	std::string Application::ResolvePath_WorkingDirectory(const std::string& path) const
	{
		std::string resultPath;

		if (m_Settings->WorkingDirectory.empty())
		{
			MU_CORE_WARN("WorkingDirectory is empty, cannot resolve path.");
			return std::string();
		}

		if (path.empty())
		{
			MU_CORE_WARN("ResolvePath_WorkingDirectory called with empty path.");
			return std::string();
		}

		// Check if the relativePath is already an absolute path
		if (path[0] == '/' || path[0] == '\\' || (path.size() > 1 && path[1] == ':'))
		{
			MU_CORE_WARN("ResolvePath_WorkingDirectory called with an absolute path: {0}", path);
			return path;
		}

		resultPath = m_Settings->WorkingDirectory + "/" + path;

		return resultPath;
	}

	std::string Application::ResolvePath_ProjectDirectory(const std::string& path) const
	{
		std::string resultPath;

		if (m_Settings->ProjectDirectory.empty())
		{
			MU_CORE_WARN("ProjectDirectory is empty, cannot resolve path.");
			return std::string();
		}

		if (path.empty())
		{
			MU_CORE_WARN("ResolvePath_ProjectDirectory called with empty path.");
			return std::string();
		}

		// Check if the path is already an absolute path
		if (path[0] == '/' || path[0] == '\\' || (path.size() > 1 && path[1] == ':'))
		{
			MU_CORE_WARN("ResolvePath_ProjectDirectory called with an absolute path: {0}", path);
			return path;
		}

		resultPath = m_Settings->ProjectDirectory + "/" + path;

		return resultPath;
	}

	std::string Application::ResolvePath_AssetsDirectory(const std::string& path) const
	{
		std::string resultPath;

		if (m_Settings->AssetsDirectory.empty())
		{
			MU_CORE_WARN("AssetsDirectory is empty, cannot resolve path.");
			return std::string();
		}

		if (path.empty())
		{
			MU_CORE_WARN("ResolvePath_AssetsDirectory called with empty path.");
			return std::string();
		}

		// Check if the relativePath is already an absolute path
		if (path[0] == '/' || path[0] == '\\' || (path.size() > 1 && path[1] == ':'))
		{
			MU_CORE_WARN("ResolvePath_AssetsDirectory called with an absolute path: {0}", path);
			return path;
		}

		resultPath = m_Settings->AssetsDirectory + "/" + path;

		return resultPath;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		MU_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		MU_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		m_Settings->Width = e.GetWidth();
		m_Settings->Height = e.GetHeight();
		return false;
	}

	MutoResult Application::InitFileSystem()
	{
		MutoResult result;

		if (GW::GReturn::SUCCESS != m_Settings->FileSystem.Create())
		{
			result = MutoResult(MU_RETURN::FAILURE, "Failed to create file system.");
			MU_CORE_ERROR("Failed to create file system.");
			return result;
		}

		char currentWorkingDirectory[255];
		if (GW::GReturn::SUCCESS != m_Settings->FileSystem.GetCurrentWorkingDirectory(currentWorkingDirectory, sizeof(currentWorkingDirectory)))
		{
			result = MutoResult(MU_RETURN::FAILURE, "Failed to get current working directory.");
			MU_CORE_ERROR("Failed to get current working directory.");
			return result;
		}
		else
		{
			m_Settings->WorkingDirectory = currentWorkingDirectory;
			MU_CORE_INFO("Current working directory: {0}", m_Settings->WorkingDirectory);
		}

		if (!m_Settings->WorkingDirectory.empty())
		{
			m_Settings->ProjectDirectory = m_Settings->WorkingDirectory + "/Project";
			MU_CORE_INFO("Project directory is: {0}", m_Settings->ProjectDirectory);
		}
		else
		{
			MU_CORE_WARN("Working directory is empty, cannot create project directory path.");
		}

		if (!m_Settings->ProjectDirectory.empty())
		{
			m_Settings->AssetsDirectory = m_Settings->ProjectDirectory + "/Assets";
			MU_CORE_INFO("Assets directory is: {0}", m_Settings->AssetsDirectory);
		}
		else
		{
			MU_CORE_WARN("Project directory is empty, cannot create assets directory path.");
		}

		return result;
	}

	MutoResult Application::InitFileSystem(ApplicationSettings& settings)
	{
		MutoResult result;
		if (GW::GReturn::SUCCESS != settings.FileSystem.Create())
		{
			result = MutoResult(MU_RETURN::FAILURE, "Failed to create file system.");
			MU_CORE_ERROR("Failed to create file system.");
			return result;
		}

		char currentWorkingDirectory[255];
		if (settings.WorkingDirectory.empty())
		{
			if (GW::GReturn::SUCCESS != settings.FileSystem.GetCurrentWorkingDirectory(currentWorkingDirectory, sizeof(currentWorkingDirectory)))
			{
				result = MutoResult(MU_RETURN::FAILURE, "Failed to get current working directory.");
				MU_CORE_ERROR("Failed to get current working directory.");
				return result;
			}
			else
			{
				settings.WorkingDirectory = currentWorkingDirectory;
				MU_CORE_INFO("Current working directory: {0}", settings.WorkingDirectory);
			}
		}
		else
		{
			if (GW::GReturn::SUCCESS != settings.FileSystem.SetCurrentWorkingDirectory(settings.WorkingDirectory.c_str()))
			{
				result = MutoResult(MU_RETURN::FAILURE, "Failed to set current working directory.");
				MU_CORE_ASSERT(false, "Failed to set current working directory.");
				return result;
			}
			else
			{
				MU_CORE_INFO("Current working directory: {0}", settings.WorkingDirectory);
			}
		}

		if (settings.ProjectDirectory.empty())
		{
			settings.ProjectDirectory = settings.WorkingDirectory + "/Project";
			MU_CORE_INFO("Project Directory is: {0}", settings.ProjectDirectory);
		}
		else
		{
			MU_CORE_INFO("Project Directory is: {0}", settings.ProjectDirectory);
		}

		if (settings.AssetsDirectory.empty())
		{
			settings.AssetsDirectory = settings.ProjectDirectory + "/Assets";
			MU_CORE_INFO("Assets Directory is: {0}", settings.AssetsDirectory);
		}
		else
		{
			MU_CORE_INFO("Assets Directory is: {0}", settings.AssetsDirectory);
		}

		return result;
	}
}
