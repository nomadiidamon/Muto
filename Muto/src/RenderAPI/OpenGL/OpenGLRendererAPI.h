#pragma once

#include "Renderer/RendererAPI.h"
#include <glm/glm.hpp>
#include <memory>

namespace Muto {

	/// @class OpenGLRendererAPI
	/// @brief An implementation of the RendererAPI for OpenGL.
	/// @note Should only be called by the RenderCommand class.
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		/// @brief Initializes the OpenGL rendering API.
		virtual void Init() override;
		/// @brief Sets the viewport dimensions for OpenGL.
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		/// @brief Sets the clear color for OpenGL.
		virtual void SetClearColor(const glm::vec4& color) override;
		/// @brief Clears the OpenGL rendering buffers.
		virtual void Clear() override;
		/// @brief Draws indexed geometry using the provided vertex array in OpenGL.
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}