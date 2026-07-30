#pragma once
/// @file RenderCommand.h
/// @author Damon S. Green II
/// @brief Defines the RenderCommand class, which provides an interface for issuing rendering commands. The RenderCommand class is a static

#include "RendererAPI.h"

namespace Muto {

	/// @class RenderCommand
	/// @brief A static class that provides an interface for issuing rendering commands.
	class RenderCommand 
	{
	public:
		
		/// @brief Initializes the rendering API.
		inline static void Init() 
		{
			s_RendererAPI->Init();
		}

		/// @brief Sets the viewport dimensions for the renderer.
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) 
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		/// @brief Sets the clear color for the renderer.
		inline static void SetClearColor(const glm::vec4& color) 
		{
			s_RendererAPI->SetClearColor(color);
		}

		/// @brief Clears the rendering buffers.
		inline static void Clear() 
		{
			s_RendererAPI->Clear();
		}

		/// @brief Draws indexed geometry using the specified vertex array and index count.
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}