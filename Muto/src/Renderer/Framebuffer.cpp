#include "mupch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLFramebuffer.h"

namespace Muto {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::RAPI_None:    MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::RAPI_OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}