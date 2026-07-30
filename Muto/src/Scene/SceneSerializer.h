#pragma once
/// @file SceneSerializer.h
/// @author Damon S. Green II
/// @brief Defines the SceneSerializer class, which handles serialization and deserialization of scenes.
/// @note The SceneSerializer class provides methods for saving and loading scenes to and from files.

#include "Core/Base.h"
#include "Scene.h"

namespace Muto {

	/// @class SceneSerializer
	/// @brief Handles serialization and deserialization of scenes.
	/// @note Serialization is currently only Text-based (YAML) and is not optimized for performance. Future versions may include a binary format for faster loading times.
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		Ref<Scene> m_Scene;
	};
}