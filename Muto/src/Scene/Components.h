#pragma once
/// @file Components.h
/// @author Damon S. Green II
/// @brief Defines various components that can be attached to entities within a scene.
/// @note Components include UUID, Name, Transform, SpriteRenderer, SubTexture, TextureAnimation, Camera, and NativeScript.
/// @todo Move GLM Enable Experimental to Math.h and remove from here

#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"
#include "ParticleSystem/ParticleSystem.h"
#include "SceneCamera.h"
#include "Core/Random.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Muto {
	/// @brief Universally Unique Identifier 
	/// 
	/// A simple wrapper around a string representing a UUID.
	struct UUID {
		/// @brief The string representation of the UUID.
		std::string ID;

		UUID() { ID = Random::UUID(); }
		UUID(const std::string& id)
			: ID{ id } {
		}
		operator std::string& () { return ID; }
		operator const std::string& () const { return ID; }
	};
	
	/// @brief Component that holds a UUID.
	struct UUIDComponent {
		/// @brief The UUID of the owning entity.
		UUID ID;

		UUIDComponent()
			: ID() {
		}
		UUIDComponent(const UUIDComponent&) = default;
		UUIDComponent(const std::string& id)
			: ID{ id } {
		}

	};

	/// @brief Component that holds the name of an entity.
	struct NameComponent
	{
		/// @brief The name of the owning entity.
		std::string Name;

		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name)
			: Name(name) {
		}
		operator std::string& () { return Name; }
		operator const std::string& () const { return Name; }
		std::string& GetName() { return Name; }
	};

	/// @brief Component that holds the transform of an entity.
	struct TransformComponent
	{
		/// @brief Translation (position) vector.
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		/// @brief Rotation vector (in radians).
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		/// @brief Scale vector.
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		/// @brief Constructor that initializes the translation with a 3D vector.
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {
		}

		/// @brief Calculates and returns the transformation matrix.
		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	/// @brief Component that holds sprite rendering data.
	struct SpriteRendererComponent
	{
		/// @brief Color of the sprite.
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		/// @brief Texture of the sprite.
		Ref<Texture2D> Texture = nullptr;
		/// @brief Tiling factor for the texture.
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		/// @brief Constructor that initializes the color.
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {
		}

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }

		/// @brief Returns the color of the sprite.
		glm::vec4& GetColor() { return Color; }

		/// @brief whether the texturing is enabled
		bool TextureEnabled = false;

		/// @brief whether the sprite should always face the camera
		///
		/// WIP
		bool Billboard = false;
	};

	/// @brief Component that holds sub-texture data for sprites.
	struct SubTextureComponent
	{
		/// @brief The sub-texture reference.
		Ref<SubTexture2D> SubTexture;
		/// @brief Tiling factor for the sub-texture.
		glm::vec2 TilingFactor = { 1.0f, 1.0f };
		/// @brief Offset for the sub-texture.
		glm::vec2 Offset = { 0.0f, 0.0f };
		

		SubTextureComponent() = default;

		/// @brief Constructor that initializes the sub-texture from a full texture.
		SubTextureComponent(const Ref<Texture2D>& texture)
			: SubTexture(SubTexture2D::CreateFromCoords(texture, { 0, 0 }, { texture->GetWidth(), texture->GetHeight() })) {
		}
		/// @brief Constructor that initializes the sub-texture directly.
		SubTextureComponent(const Ref<SubTexture2D>& subTexture)
			: SubTexture(subTexture) {
		}
		/// @brief Copy constructor.
		void SetTexture(const Ref<Texture2D>& texture) {
			SubTexture = SubTexture2D::CreateFromCoords(texture, { 0, 0 }, { texture->GetWidth(), texture->GetHeight() });
		}
		
		/// @brief Sets the tiling factor for the sub-texture.
		void SetTilingFactor(const glm::vec2& tiling) {
			TilingFactor = tiling;
		}

		/// @brief Sets the offset for the sub-texture.
		void SetOffset(const glm::vec2& offset) {
			Offset = offset;
		}

		operator Ref<SubTexture2D>& () { return SubTexture; }
		operator const Ref<SubTexture2D>& () const { return SubTexture; }
		Ref<SubTexture2D>& GetSubTexture() { return SubTexture; }
	};

	/// @brief Animates through a series of sub textures
	///
	/// (can be used with full textures)
	struct TextureAnimationComponent
	{
		/// @brief The list of sub-textures for the animation.
		std::vector<Ref<SubTexture2D>> SubTextures;
		/// @brief The current frame index.
		int CurrentFrame = 0;
		/// @brief Time per frame in seconds.
		float FrameTime = 0.6f; // Time per frame in seconds
		/// @brief Accumulated time for frame switching.
		float TimeAccumulator = 0.0f; // per-instance accumulator

		bool IsLooping = true;


		TextureAnimationComponent() = default;
		TextureAnimationComponent(const TextureAnimationComponent&) = default;
		/// @brief Constructor that initializes the sub-textures and frame time.
		///
		/// @param subTextures Vector of sub-textures for the animation.
		/// @param frameTime Time per frame in seconds.
		TextureAnimationComponent(const std::vector<Ref<SubTexture2D>>& subTextures, float frameTime)
			: SubTextures(subTextures), FrameTime(frameTime) {
		}
		operator std::vector<Ref<SubTexture2D>>& () { return SubTextures; }
		operator const std::vector<Ref<SubTexture2D>>& () const { return SubTextures; }

		Ref<SubTexture2D> GetCurrentSubTexture() { 
			if (SubTextures.empty())
				return nullptr;
			if (CurrentFrame < 0) CurrentFrame = 0;
			if (CurrentFrame >= (int)SubTextures.size()) CurrentFrame = (int)SubTextures.size() - 1;
			return SubTextures[CurrentFrame]; 
		}
		std::vector<Ref<SubTexture2D>>& GetSubTextures() { return SubTextures; }

		/// @brief Returns the index of the current frame.
		int GetCurrentFrame() const { return CurrentFrame; }

		/// @brief Updates the animation based on the elapsed time.
		///
		/// @param deltaTime The elapsed time since the last update.
		void Update(float deltaTime) {
			if (SubTextures.empty() || FrameTime <= 0.0f)
				return;

			TimeAccumulator += deltaTime;
			while (TimeAccumulator >= FrameTime) {
				CurrentFrame = (CurrentFrame + 1) % static_cast<uint32_t>(SubTextures.size());
				TimeAccumulator -= FrameTime;
			}
		}
	};

	/// @brief Component that holds camera data.
	struct CameraComponent
	{
		/// @brief The scene camera.
		SceneCamera Camera;

		/// @brief Whether this camera is the primary camera.
		///
		/// If multiple cameras exist, the primary camera for rendering will be the first one found marked as primary.
		bool Primary = true;

		/// @brief Whether the aspect ratio is fixed.
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

	};


	class ScriptableEntity;
	class Timestep;

	/// @brief Component that holds scripting data for an entity.
	struct NativeScriptComponent
	{
		/// @brief Pointer to the instance of the scriptable entity.
		ScriptableEntity* Instance = nullptr;

		/// @brief Function pointer to instantiate the script.
		ScriptableEntity* (*InstantiateScript)();
		/// @brief Function pointer to destroy the script.
		void (*DestroyScript)(NativeScriptComponent*);

		/// @brief Binds a script type to this component.
		///
		/// @tparam T The type of the script to bind.
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*> (new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};


	struct ParticleSystemComponent
	{
		ParticleSystem ParticleSystem;

		ParticleSystemComponent() = default;
		ParticleSystemComponent(const ParticleSystemComponent&) = default;
		ParticleSystemComponent(const int maxParticles)
			: ParticleSystem(maxParticles) {
		}

	};

}