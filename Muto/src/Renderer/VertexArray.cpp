#include "mupch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace Muto {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::RAPI_None:		MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::RAPI_OpenGL:		return CreateRef<OpenGLVertexArray>();
		}
		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}