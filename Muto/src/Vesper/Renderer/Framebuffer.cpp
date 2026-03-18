#include "vzpch.h"
#include "Framebuffer.h"

#include "Vesper/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLFramebuffer.h"

namespace Vesper {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		VZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}