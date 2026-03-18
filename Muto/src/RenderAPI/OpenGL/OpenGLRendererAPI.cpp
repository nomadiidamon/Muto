#include "vzpch.h"
#include "Vesper/Renderer/RendererAPI.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Vesper {
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		VZ_PROFILE_FUNCTION();

		glViewport(x, y, width, height);
	}

	void Vesper::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		VZ_PROFILE_FUNCTION();

		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		VZ_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		VZ_PROFILE_FUNCTION();
		
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		if (count == 0)
			return;

		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
		vertexArray->Unbind();
	}
}