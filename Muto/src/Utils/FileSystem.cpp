#include "mupch.h"
#include "Utils/PlatformUtils.h"

#include <filesystem>

namespace Muto {

	bool FileSystem::m_Initialized = false;
	std::string FileSystem::m_RootEngineDirectory = "";
	std::string FileSystem::m_RootEditorDirectory = "";
	std::string FileSystem::m_ResourcesDirectory = "";
	std::string FileSystem::m_AssetsDirectory = "";
	std::string FileSystem::m_ProjectsDirectory = "";
	std::string FileSystem::m_CurrentProjectDirectory = "";

	void FileSystem::Initialize()
	{
		if (m_Initialized)
			return;

		m_Initialized = true;
		const std::filesystem::path workingDirectory = std::filesystem::current_path();
		m_RootEngineDirectory = workingDirectory.string();
		m_RootEditorDirectory = workingDirectory.string();
		m_ResourcesDirectory = (workingDirectory / "Resources").string();
		m_AssetsDirectory = (workingDirectory / "assets").string();
		m_ProjectsDirectory = (workingDirectory / "Projects").string();
		m_CurrentProjectDirectory = (std::filesystem::path(m_ProjectsDirectory) / "DefaultProject").string();

		MU_CORE_TRACE("FileSystem initialized");
	}

	std::string FileSystem::GetCurrentWorkingDirectory()
	{
		return std::filesystem::current_path().string();
	}

	std::string FileSystem::GetAbsolutePath(const std::string& relativePath)
	{
		return std::filesystem::absolute(relativePath).lexically_normal().string();
	}

	std::string FileSystem::GetTravelingUpPath(const std::string& path)
	{
		return std::filesystem::path(path).parent_path().string();
	}

}