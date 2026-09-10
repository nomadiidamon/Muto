#pragma once

/// @file ResourceManager.h
/// @author Damon S. Green II
/// @brief ResourceManager class for managing application resources and pathing.

namespace Muto
{
	/// @brief Normalizes path separators to forward slashes for cross-platform consistency
	static std::string NormalizePath(const std::string& path)
	{
		std::string normalized = path;
		for (char& c : normalized)
		{
			if (c == '\\')
				c = '/';
		}
		return normalized;
	}

	/// @brief Joins two path segments with proper separator handling
	static std::string JoinPaths(const std::string& base, const std::string& relative)
	{
		if (base.empty())
			return relative;
		if (relative.empty())
			return base;

		std::string result = base;
		
		// Ensure base doesn't end with a separator
		if (result.back() == '/' || result.back() == '\\')
			result.pop_back();

		result += '/';
		
		// Append relative path, removing leading separators
		size_t start = 0;
		while (start < relative.size() && (relative[start] == '/' || relative[start] == '\\'))
			start++;
		
		result += relative.substr(start);
		return result;
	}

	/// @brief Determines whether the given path is an absolute path (Unix-style, Windows-style, or drive-letter).
	static bool IsAbsolutePath(const std::string& path)
	{
		if (path.empty())
			return false;

		if (path[0] == '/' || path[0] == '\\')
			return true;

		if (path.size() > 1 && path[1] == ':')
			return true;

		return false;
	}

	/// @class ResourceManager
	/// @brief The ResourceManager class is responsible for managing application resources and pathing.
	/// @todo Implement resource management functionality, including loading, caching, and unloading resources.
	/// @note Pull the pathing and resource management out of the Application class and into this class to keep the Application class clean and focused on application lifecycle management.
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

	};
}
