#include "CorePCHeader.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Core
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case Configuration::RendererAPI::OpenGL:  return new OpenGLVertexArray();
		case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!");
		return nullptr;
	}
}