#include "mupch.h"
#include "Shader.h"

#include "Renderer.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

namespace Muto {

	Ref<Shader> Shader::Create(const std::string& filepath) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(filepath);
		}
		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		MU_PROFILE_FUNCTION();
		MU_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		MU_PROFILE_FUNCTION();
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Muto::Ref<Muto::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		MU_PROFILE_FUNCTION();
		auto shader = Shader::Create(filepath);
		Add(Ref<Shader>(shader));
		return shader;
	}

	Muto::Ref<Muto::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		MU_PROFILE_FUNCTION();
		auto shader = Shader::Create(filepath);
		Add(Ref<Muto::Shader>(shader));
		return shader;
	}

	Muto::Ref<Muto::Shader> ShaderLibrary::Get(const std::string& name)
	{
		MU_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		MU_PROFILE_FUNCTION();
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
