#pragma once
/// @file RendererAPI.h
/// @author Damon S. Green II
/// @brief Defines the RendererAPI class, which is an abstract class that defines the interface for a rendering API. This class is used by the Renderer class to abstract away the underlying rendering API being used (e.g., OpenGL, DirectX, Vulkan, etc.).
/// @note The RendererAPI class is not intended to be used directly by the user. Instead, the Renderer class should be used to interact with the rendering API.

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Vesper {

	/// @class RendererAPI
	/// @brief An abstract class defining the interface for a rendering API.
	/// @todo Add abstraction layers (similar to OpenGL) for Vulkan and DirectX and implement corresponding RendererAPI subclasses for each API.
	/// @todo Add NVRHI as an additional API for DirectX and Vulkan to simplify cross-platform rendering support.
	class RendererAPI {
	public:

		/// @brief API that can be used by the Renderer.
		enum class API {
			None = 0,
			OpenGL = 1,
		};

	public:
		virtual ~RendererAPI() = default;
		/// @brief Initializes the rendering API.
		virtual void Init() = 0;
		/// @brief Sets the viewport dimensions.
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		/// @brief Sets the clear color for the rendering API.
		virtual void SetClearColor(const glm::vec4& color) = 0;
		/// @brief Clears the rendering buffers.
		virtual void Clear() = 0;

		/// @brief Draws indexed geometry using the provided vertex array.
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		/// @brief Returns the current rendering API.
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};


}