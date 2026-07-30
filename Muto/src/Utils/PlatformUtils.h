#pragma once
/// @file PlatformUtils.h
/// @author Damon S. Green II
/// @brief Declares platform-specific utilities for file dialogs and file system operations.

#include <string>

namespace Muto {
	
	/// @class FileDialogs
	/// @brief Cross-platform file dialog utilities.
	class FileDialogs
	{
	public:
		/// @brief Opens a file dialog to select a file to open.
		///
		/// @param filter The file type filter for the dialog.
		/// @return The selected file path or an empty string if cancelled.
		static std::string OpenFile(const char* filter);

		/// @brief Opens a file dialog to select a location to save a file.
		///
		/// @param filter The file type filter for the dialog.
		/// @return The selected file path or an empty string if cancelled.
		static std::string SaveFile(const char* filter);
	};


	/// WIP
	class FileSystem
	{
	public:
		static void Initialize();
		static std::string GetCurrentWorkingDirectory();
		static std::string GetAbsolutePath(const std::string& relativePath);
		static std::string GetTravelingUpPath(const std::string& path);
		static bool IsInitialized() { return m_Initialized; }

		static bool m_Initialized;
		static std::string m_RootEngineDirectory;
		static std::string m_RootEditorDirectory;
		static std::string m_ResourcesDirectory;
		static std::string m_AssetsDirectory;
		static std::string m_ProjectsDirectory;
		static std::string m_CurrentProjectDirectory;
	};


};