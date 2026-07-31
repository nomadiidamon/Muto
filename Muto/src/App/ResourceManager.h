#pragma once

/// @file ResourceManager.h
/// @author Damon S. Green II
/// @brief ResourceManager class for managing application resources and pathing.

namespace Muto
{
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
