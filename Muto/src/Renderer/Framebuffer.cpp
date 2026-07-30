#include "mupch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLFramebuffer.h"

namespace Muto {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}