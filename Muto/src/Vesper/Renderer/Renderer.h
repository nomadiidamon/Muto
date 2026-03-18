#pragma once
/// @file Renderer.h
/// @author Damon S. Green II
/// @brief Defines the Renderer class, which is responsible for managing rendering operations in the Vesper engine. The Renderer class provides a high-level interface for rendering scenes, submitting draw calls, and managing rendering state.
/// @note The Renderer class is a static class that provides an interface for rendering operations. It abstracts away the underlying rendering API and provides a consistent interface for rendering across different platforms and graphics APIs.

#include "Vesper/Renderer/RenderCommand.h"
#include "Vesper/Renderer/OrthographicCamera.h"
#include "Vesper/Renderer/Shader.h"

namespace Vesper {
	
	/// @class Renderer
	/// @brief The main renderer class responsible for managing rendering operations.
	class Renderer {

	public:

		/// @brief Initializes the renderer.
		/// @note This initializes both the RenderCommand and Renderer2D systems.
		static void Init();

		/// @brief Handles window resize events by resizing the viewport.
		static void OnWindowResize(uint32_t width, uint32_t height);

		/// @brief Begins a new scene with the given orthographic camera.
		/// @param camera The orthographic camera defining the view and projection for the scene.
		/// @todo Support for other camera types.
		static void BeginScene(OrthographicCamera& camera);

		/// @brief Ends the current scene.
		/// @note Currently does nothing as scene closure is automatic, but could be useful for a render interface
		static void EndScene();

		/// @brief Submits a draw call with the specified shader, vertex array, and transform.
		///
		/// @param shader The shader to use for rendering.
		/// @param vertexArray The vertex array to draw.
		/// @param transform The transformation matrix to apply.
		/// @todo Set up a command list to encapsulate this for draw order control
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		/// @brief Retrieves the current rendering API.
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		/// @brief Scene data structure containing view-projection matrix.
		struct SceneData {
			/// @brief The combined view-projection matrix for the scene.
			glm::mat4 ViewProjectionMatrix;
		};

		/// @brief Pointer to the current scene data.
		static SceneData* s_SceneData;

	};
}