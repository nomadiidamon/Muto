#pragma once
/// @file Texture.h
/// @author Damon S. Green II
/// @brief Defines the Texture class, which is an abstraction for a texture, and the TextureLibrary class, which manages and stores textures.
/// @note The Texture class provides an interface for working with textures, while the TextureLibrary class allows for easy management and retrieval of textures by name.

namespace Muto {

	class Texture2D;

	/// @class Texture
	/// @brief An abstraction for a texture.
	class Texture
	{
	public:
		virtual ~Texture() = default;

		/// @brief Returns the width of the texture.
		virtual uint32_t GetWidth() const = 0;
		/// @brief Returns the height of the texture.
		virtual uint32_t GetHeight() const = 0;
		/// @brief Returns the renderer ID of the texture.
		virtual uint32_t GetRendererID() const = 0;

		/// @brief Binds the texture to the specified slot for use.
		virtual void Bind(uint32_t slot = 0) const = 0;

		/// @brief Sets the data of the texture.
		///
		/// @param data Pointer to the data to be set.
		/// @param size Size of the data in bytes.
		virtual void SetData(void* data, uint32_t size) = 0;

		virtual bool operator==(const Texture2D& other) const = 0;
		virtual std::string GetName() const = 0;
	};

	/// @class Texture2D
	/// @brief An abstraction for a 2D texture.
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};


	/// @class TextureLibrary
	/// @brief A library for managing and storing textures.
	/// 
	/// No current serialization implemented.
	class TextureLibrary 
	{
	public:
		/// @brief Adds a texture to the library with the specified name.
		void Add(const std::string& name, const Ref<Texture2D>& texture);
		/// @brief Adds a texture to the library using its own name.
		void Add(const Ref<Texture2D>& texture);
		/// @brief Loads a texture from the specified filepath and adds it to the library.
		Ref<Texture2D> Load(const std::string& filepath);
		/// @brief Loads a texture from the specified filepath and adds it to the library with the given name.
		Ref<Texture2D> Load(const std::string& name, const std::string& filepath);
		/// @brief Retrieves a texture from the library by name.
		Ref<Texture2D> Get(const std::string& name) const;
		/// @brief Checks if a texture with the specified name exists in the library.
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Texture2D>> m_Textures;

	};
}
