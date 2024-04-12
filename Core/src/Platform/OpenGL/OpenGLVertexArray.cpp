#include "CorePCHeader.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Core
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::vecFloat:    return GL_FLOAT;
		case ShaderDataType::vecFloat2:   return GL_FLOAT;
		case ShaderDataType::vecFloat3:   return GL_FLOAT;
		case ShaderDataType::vecFloat4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::vecInt:      return GL_INT;
		case ShaderDataType::vecInt2:     return GL_INT;
		case ShaderDataType::vecInt3:     return GL_INT;
		case ShaderDataType::vecInt4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateBuffers(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		const auto& layout = vertexBuffer->GetLayout();
		const auto& elements = layout.GetElements();

		for (uint32_t index = 0; index < elements.size(); index++)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				elements[index].GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(elements[index].Type), 
				elements[index].Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(),
				(const void*)elements[index].Offset);
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffex)
	{
		glBindVertexArray(m_RendererID);
		indexBuffex->Bind();

		m_IndexBuffer = indexBuffex;
	}
}