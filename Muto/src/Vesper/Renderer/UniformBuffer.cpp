#include "vzpch.h"
#include "UniformBuffer.h"

#include "Vesper/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLUniformBuffer.h"

namespace Vesper {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    VZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		VZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}