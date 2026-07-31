#pragma once
/// @file Shader.h
/// @author Damon S. Green II
/// @brief Defines the Shader class, which is an abstraction for a shader program, and the ShaderLibrary class, which manages and stores shaders.
/// @note The Shader class provides an interface for setting uniform variables in the shader program, while the ShaderLibrary class allows for easy management and retrieval of shaders by name.

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Muto {

	/// @class Shader
	/// @brief An abstraction for a shader program.
	class Shader
	{
	public:

		virtual ~Shader() = default;

		/// @brief connects the shader program for use.
		virtual void Bind() const = 0;
		/// @brief disconnects the shader program.
		virtual void Unbind() const = 0;

		/// @brief Sets a 4x4 matrix uniform in the shader.
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		/// @brief Sets a 4-component float vector uniform in the shader.
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		/// @brief Sets a 3-component float vector uniform in the shader.
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		/// @brief Sets a single float uniform in the shader.
		virtual void SetFloat(const std::string& name, float value) = 0;
		/// @brief Sets a single integer uniform in the shader.
		virtual void SetInt(const std::string& name, int value) = 0;
		/// @brief Sets an array of integers uniform in the shader.
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

		/// <summary>
		/// Creates a new shader from vertex and fragment shader source code.
		/// </summary>
		/// <param name="name">The name to assign to the shader.</param>
		/// <param name="vertexSrc">The vertex shader source code as a string.</param>
		/// <param name="fragmentSrc">The fragment shader source code as a string.</param>
		/// <returns>A reference to the newly created shader object.</returns>
		/// @todo Adjust function to return a MutoResult and have the shader as an out parameter, to allow for error handling during shader compilation.
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		/// <summary>
		/// Creates a shader from a file.
		/// </summary>
		/// <param name="filepath">The path to the shader file to load.</param>
		/// <returns>A reference to the created shader object.</returns>
		/// @todo Adjust function to return a MutoResult and have the shader as an out parameter, to allow for error handling during shader compilation.
		static Ref<Shader> Create(const std::string& filepath);

		virtual const std::string& GetName() const = 0;

	};

	/// @class ShaderLibrary
	/// @brief A library for managing and storing shaders.
	class ShaderLibrary
	{
	public:
		/// @brief Adds a shader to the library with the specified name.
		void Add(const std::string& name, const Ref<Shader>& shader);
		/// @brief Adds a shader to the library using its own name.
		void Add(const Ref<Shader>& shader);

		/// @brief Loads a shader from the specified filepath and adds it to the library.
		Ref<Shader> Load(const std::string& filepath);
		/// @brief Loads a shader from the specified filepath and adds it to the library with the given name.
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		/// @brief Retrieves a shader from the library by name.
		Ref<Shader> Get(const std::string& name);

		/// @brief Checks if a shader with the specified name exists in the library.
		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}
