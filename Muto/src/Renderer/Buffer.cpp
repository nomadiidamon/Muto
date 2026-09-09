#include "mupch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "RenderAPI/OpenGL/OpenGLBuffer.h"


namespace Muto {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::RAPI_None:		MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::RAPI_OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);
		}
		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::RAPI_None:		MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::RAPI_OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{

		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::RAPI_None:		MU_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::RAPI_OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		MU_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}