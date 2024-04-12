#include "CorePCHeader.h"

#include "Renderer/UniformBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Core
{
	UniformBuffer* UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case Configuration::RendererAPI::OpenGL:  return new OpenGLUniformBuffer(size, binding);
		case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!"); 
		return nullptr;
	}
}