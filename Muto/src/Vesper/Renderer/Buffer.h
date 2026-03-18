#pragma once
/// @file Buffer.h
/// @author Damon S. Green II
/// @brief Defines the Buffer classes used for vertex and index data in rendering.

namespace Vesper {

	/// @brief The different data types that can be used in shaders.
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	/// @brief Returns the size in bytes of the given ShaderDataType.
	///
	/// @param type The ShaderDataType to get the size of.
	/// @return The size in bytes of the ShaderDataType.
	/// Will assert if the type is unknown.
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}
		VZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	/// @brief Represents a single element in a buffer layout.
	struct BufferElement {
		/// @brief The name of the buffer element.
		std::string Name;
		/// @brief The data type of the buffer element.
		ShaderDataType Type;
		/// @brief The size in bytes of the buffer element.
		uint32_t Size;
		/// @brief The offset in bytes of the buffer element from the start of the buffer.
		uint32_t Offset;
		/// @brief Whether the buffer element is normalized.
		bool Normalized;

		BufferElement() {}
		/// @brief Constructs a BufferElement with the given type, name, and normalization flag.
		///
		/// @param type The ShaderDataType of the buffer element.
		/// @param name The name of the buffer element.
		/// @param normalized Whether the buffer element is normalized.
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		/// @brief Returns the number of components in the buffer element based on its ShaderDataType.
		uint32_t GetComponentCount() const {
			switch (Type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}
			VZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	/// @class BufferLayout
	/// @brief Represents the layout of a buffer, consisting of multiple BufferElements.
	class BufferLayout {
	public:
		BufferLayout(){}

		/// @brief Constructs a BufferLayout with the given list of BufferElements.
		///
		/// @param elements The list of BufferElements that make up the layout.
		/// Automatically calculates offsets and stride.
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements), m_Stride(0)
		{
			CalculateOffsetsAndStride();
		}


		/// @brief Returns the list of BufferElements in the layout.
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		/// @brief Returns the stride (total size in bytes) of the buffer layout.
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }



	private:
		/// @brief Calculates the offsets and stride for the buffer layout based on its elements.
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};


	/// @class VertexBuffer
	/// @brief Abstract base class for a vertex buffer.
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;


		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	/// @class IndexBuffer
	/// @brief Abstract base class for an index buffer.
	///
	/// Currently only supports uint32_t indices
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}