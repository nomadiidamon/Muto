#include "mupch.h"
/// @file WindowsPlatformUtils.cpp
/// @author Damon S. Green II
/// @brief Windows-specific implementations of file dialogs and file system utilities.
/// @todo Move GLFW expose native win32 define to platform detection
#include "Utils/PlatformUtils.h"
#include "App/Application.h"
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Muto {
	
	std::string FileDialogs::OpenFile(const char* filter) {

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
			return std::string(ofn.lpstrFile);
		return std::string();
	}

	std::string FileDialogs::SaveFile(const char* filter) {

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();

	}




	bool FileSystem::m_Initialized = false;
	std::string FileSystem::m_RootEngineDirectory = "";
	std::string FileSystem::m_RootEditorDirectory = "";
	std::string FileSystem::m_ResourcesDirectory = "";
	std::string FileSystem::m_AssetsDirectory = "";
	std::string FileSystem::m_ProjectsDirectory = "";
	std::string FileSystem::m_CurrentProjectDirectory = "";

	void FileSystem::Initialize() {
		if (m_Initialized)
			return;
		m_Initialized = true;

		// Set Root Engine Directory
		m_RootEngineDirectory = GetTravelingUpPath(GetTravelingUpPath(GetTravelingUpPath(GetAbsolutePath("."))));
		// Set Root Editor Directory
		m_RootEditorDirectory = GetAbsolutePath("../../Vesper-Editor/");
		// Set Resources Directory
		m_ResourcesDirectory = GetAbsolutePath(m_RootEngineDirectory + "/Resources/");
		// Set Assets Directory
		m_AssetsDirectory = GetAbsolutePath(m_RootEditorDirectory + "/assets");
		// Set Projects Directory
		m_ProjectsDirectory = GetAbsolutePath(m_RootEngineDirectory + "/Projects");
		// Set Current Project Directory
		m_CurrentProjectDirectory = GetAbsolutePath(m_ProjectsDirectory + "/DefaultProject");



		// Log Directories for Debugging
		MU_CORE_TRACE("FileSystem initialized");
		MU_CORE_TRACE("FileSystem Directories:");
		MU_CORE_TRACE("Root Engine Directory : " + m_RootEngineDirectory);
		MU_CORE_TRACE("Root Editor Directory : " + m_RootEditorDirectory);
		MU_CORE_TRACE("Resources Directory   : " + m_ResourcesDirectory);
		MU_CORE_TRACE("Assets Directory      : " + m_AssetsDirectory);
		MU_CORE_TRACE("Projects Directory    : " + m_ProjectsDirectory);
		MU_CORE_TRACE("Current Project Directory : " + m_CurrentProjectDirectory);
	}

	std::string FileSystem::GetCurrentWorkingDirectory() {
		CHAR currentDir[256] = { 0 };
		if (GetCurrentDirectoryA(256, currentDir))
			return std::string(currentDir);
		return std::string();
	}

	std::string FileSystem::GetAbsolutePath(const std::string& relativePath) {
		char fullPath[MAX_PATH];
		if (_fullpath(fullPath, relativePath.c_str(), MAX_PATH) != nullptr) {
			return std::string(fullPath);
		}
		return std::string();
	}

	std::string FileSystem::GetTravelingUpPath(const std::string& path) {
		size_t pos = path.find_last_of("/\\");
		if (pos != std::string::npos) {
			return path.substr(0, pos);
		}
		return std::string();
	}

}