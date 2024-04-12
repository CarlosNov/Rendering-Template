#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLRendererContext.h"

namespace Core
{
	RendererContext* RendererContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case Configuration::RendererAPI::OpenGL:  return new OpenGLRendererContext(static_cast<GLFWwindow*>(window));
			case Configuration::RendererAPI::Unknown: CORE_LOG_ERROR("Unknown RendererAPI"); return nullptr;
		}
	}
	
}