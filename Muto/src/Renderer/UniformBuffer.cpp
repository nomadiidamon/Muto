#include "mupch.h"
#include "UniformBuffer.h"

#include "Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLUniformBuffer.h"

namespace Muto {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}