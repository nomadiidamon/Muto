#include "mupch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <fstream>

#include <yaml-cpp/yaml.h>


namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};


	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

}

namespace Muto {


	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {

		MU_CORE_ASSERT(entity.HasComponent<UUIDComponent>(), "Entity has no UUIDComponent!");
		MU_CORE_ASSERT(entity.HasComponent<NameComponent>(), "Entity has no NameComponent!");

		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity.GetID(); // UUIDComponent
		out << YAML::Key << "NameComponent" << YAML::Value << entity.GetName();

		if (entity.HasComponent<TransformComponent>()) {
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (entity.HasComponent<CameraComponent>()) {
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComp = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComp.Camera;


			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap;

			out << YAML::Key << "Primary" << YAML::Value << cameraComp.Primary;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComp.FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.HasComponent<SpriteRendererComponent>()) {
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& src = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << src.Color;
			// Texture serialization can be added here in the future
			out << YAML::EndMap; // SpriteRendererComponent
		}
		out << YAML::EndMap; // Entity
	}

	void SceneSerializer::Serialize(const std::string& filepath) {
		YAML::Emitter out;
		out << YAML::BeginMap; // Scene
		out << YAML::Key << "Scene" << YAML::Value << m_Scene->GetName();
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq; // Entities
		m_Scene->m_Registry.view<entt::entity>().each([&](auto entityID) {

			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);

			});

		out << YAML::EndSeq; // Entities
		out << YAML::EndMap; // Scene

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		MU_CORE_ASSERT(false, "Not implemented");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath) {

		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		MU_CORE_TRACE("Deserializing scene: {0}", sceneName);

		YAML::Node entities = data["Entities"];
		if (entities)
		{
			for (auto entityNode : entities)
			{
				std::string uuid = entityNode["Entity"].as<std::string>();
				std::string name;
				YAML::Node nameNode = entityNode["NameComponent"];
				if (nameNode)
					name = nameNode.as<std::string>();
				MU_CORE_TRACE("Deserialized entity with ID: {0}, name: {1}", uuid, name);
				Entity deserializedEntity = m_Scene->CreateEntity(name, uuid);
				YAML::Node transformNode = entityNode["TransformComponent"];
				if (transformNode)
				{
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformNode["Translation"].as<glm::vec3>();
					tc.Rotation = transformNode["Rotation"].as<glm::vec3>();
					tc.Scale = transformNode["Scale"].as<glm::vec3>();
				}
				YAML::Node cameraNode = entityNode["CameraComponent"];
				if (cameraNode)
				{
					auto& cameraComp = deserializedEntity.AddComponent<CameraComponent>();
					auto& camera = cameraComp.Camera;
					YAML::Node camProps = cameraNode["Camera"];
					camera.SetOrthographic(camProps["OrthographicSize"].as<float>(), camProps["OrthographicNear"].as<float>(), camProps["OrthographicFar"].as<float>());
					camera.SetPerspective(camProps["PerspectiveFOV"].as<float>(), camProps["PerspectiveNear"].as<float>(), camProps["PerspectiveFar"].as<float>());
					cameraComp.Primary = cameraNode["Primary"].as<bool>();
					camera.SetProjectionType((SceneCamera::ProjectionType)cameraNode["ProjectionType"].as<int>());
					cameraComp.FixedAspectRatio = cameraNode["FixedAspectRatio"].as<bool>();
				}
				YAML::Node spriteNode = entityNode["SpriteRendererComponent"];
				if (spriteNode)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
					src.Color = spriteNode["Color"].as<glm::vec4>();
				}
			}
		}
		return true;

	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		MU_CORE_ASSERT(false, "Not implemented");
		return false;
	}

}