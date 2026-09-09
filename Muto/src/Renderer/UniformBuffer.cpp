#include "mupch.h"
#include "UniformBuffer.h"

#include "Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLUniformBuffer.h"

namespace Muto {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::RAPI_None:    MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::RAPI_OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}