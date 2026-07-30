#include "mupch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace Muto {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		MU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
		}
		MU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}