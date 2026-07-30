#include "mupch.h"
#include "Texture.h"

#include "Renderer.h"
#include <string>
#include "RenderAPI/OpenGL/OpenGLTexture.h"

namespace Muto {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
		}
		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		}
		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void TextureLibrary::Add(const std::string& name, const Ref<Texture2D>& texture)
	{
		MU_PROFILE_FUNCTION();
		MU_CORE_ASSERT(!Exists(name), "Texture already exists!");
		m_Textures[name] = texture;
	}

	void TextureLibrary::Add(const Ref<Texture2D>& texture)
	{
		MU_PROFILE_FUNCTION();
		auto& name = texture->GetName();
		Add(name, texture);
	}

	Ref<Texture2D> TextureLibrary::Load(const std::string& filepath)
	{
		MU_PROFILE_FUNCTION();
		auto texture = Texture2D::Create(filepath);
		Add(texture);
		return texture;
	}

	Ref<Texture2D> TextureLibrary::Load(const std::string& name, const std::string& filepath)
	{
		MU_PROFILE_FUNCTION();
		auto texture = Texture2D::Create(filepath);
		Add(texture);
		return texture;
	}

	Ref<Texture2D> TextureLibrary::Get(const std::string& name) const
	{
		MU_PROFILE_FUNCTION();
		MU_CORE_ASSERT(Exists(name), "Texture not found!");
		return m_Textures.at(name);
	}

	bool TextureLibrary::Exists(const std::string& name) const
	{
		MU_PROFILE_FUNCTION();
		return m_Textures.find(name) != m_Textures.end();
	}
}
