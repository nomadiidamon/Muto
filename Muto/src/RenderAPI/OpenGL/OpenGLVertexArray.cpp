#include "mupch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>


namespace Muto {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::SDT_Float:		return GL_FLOAT;
		case ShaderDataType::SDT_Float2:	return GL_FLOAT;
		case ShaderDataType::SDT_Float3:	return GL_FLOAT;
		case ShaderDataType::SDT_Float4:	return GL_FLOAT;
		case ShaderDataType::SDT_Mat3:		return GL_FLOAT;
		case ShaderDataType::SDT_Mat4:		return GL_FLOAT;
		case ShaderDataType::SDT_Int:		return GL_INT;
		case ShaderDataType::SDT_Int2:		return GL_INT;
		case ShaderDataType::SDT_Int3:		return GL_INT;
		case ShaderDataType::SDT_Int4:		return GL_INT;
		case ShaderDataType::SDT_Bool:		return GL_BOOL;
		}
		MU_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		MU_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		MU_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		MU_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		MU_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		MU_PROFILE_FUNCTION();

		MU_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			MU_PROFILE_SCOPE("VertexBufferElement");
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		MU_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}