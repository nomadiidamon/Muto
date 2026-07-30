#pragma once
/// @file VertexArray.h
/// @author Damon S. Green II
/// @brief Defines the VertexArray class, which is an abstraction for a vertex array object (VAO).
/// @note The VertexArray class provides an interface for managing vertex buffers and index buffers, and includes a static Create method for instantiating vertex arrays.

#include <memory>
#include "Renderer/Buffer.h"

namespace Muto {

	/// @class VertexArray
	/// @brief An abstraction for a vertex array object (VAO).
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		/// @brief Adds a vertex buffer to the vertex array.
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		/// @brief Sets the index buffer for the vertex array.
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}