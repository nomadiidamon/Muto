#include "vzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace Vesper {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		VZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
		}
		VZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}