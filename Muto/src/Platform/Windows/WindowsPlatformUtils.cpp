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

}