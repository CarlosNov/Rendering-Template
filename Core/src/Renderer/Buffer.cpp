#include "CorePCHeader.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Core
{
	void BufferLayout::CalculateStrideAndOffset()
	{
		size_t offset = 0;
		m_Stride = 0;

		for (BufferElement& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	VertexBuffer* VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Configuration::RendererAPI::OpenGL:  return new OpenGLVertexBuffer(size);
		case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!"); 
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Configuration::RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case Configuration::RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, count);
		case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!");
		return nullptr;
	}
}