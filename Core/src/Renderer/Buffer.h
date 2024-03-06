#pragma once

namespace Core
{
	enum class ShaderDataType
	{
		None = 0, vecFloat, vecFloat2, vecFloat3, vecFloat4, vecInt, vecInt2, vecInt3, vecInt4, Mat3, Mat4, Bool
	};

	static uint32_t ShaderDataTypeSize(const ShaderDataType& shaderDataType)
	{
		switch (shaderDataType)
		{
		case ShaderDataType::vecFloat: return 4;
		case ShaderDataType::vecFloat2: return 4 * 2;
		case ShaderDataType::vecFloat3: return 4 * 3;
		case ShaderDataType::vecFloat4: return 4 * 4;
		case ShaderDataType::vecInt: return 4;
		case ShaderDataType::vecInt2: return 4 * 2;
		case ShaderDataType::vecInt3: return 4 * 3;
		case ShaderDataType::vecInt4: return 4 * 4;
		case ShaderDataType::Mat3: return 4 * 3 * 3;
		case ShaderDataType::Mat4: 4 * 4 * 4;
		case ShaderDataType::Bool: 1;
		}

		CORE_ASSERT(false, "No valid ShaderDataTyped!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::vecFloat:   return 1;
			case ShaderDataType::vecFloat2:  return 2;
			case ShaderDataType::vecFloat3:  return 3;
			case ShaderDataType::vecFloat4:  return 4;
			case ShaderDataType::Mat3:       return 3; // 3* float3
			case ShaderDataType::Mat4:       return 4; // 4* float4
			case ShaderDataType::vecInt:     return 1;
			case ShaderDataType::vecInt2:    return 2;
			case ShaderDataType::vecInt3:    return 3;
			case ShaderDataType::vecInt4:    return 4;
			case ShaderDataType::Bool:       return 1;
			}

			CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements)
		{
			CalculateStrideAndOffset();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateStrideAndOffset();
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(uint32_t size);
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	// Currently Hazel only supports 32-bit index buffers
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}