#include "CorePCHeader.h"

#include "Renderer/Framebuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Core
{
	Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case Configuration::RendererAPI::OpenGL:  return new OpenGLFramebuffer(spec);
			case Configuration::RendererAPI::Unknown: CORE_ASSERT(false, "RendererAPI::Unknown is currently not supported!"); return nullptr;
		}

		CORE_ASSERT(false, "RendererAPI not supported!");
		return nullptr;
	}
}