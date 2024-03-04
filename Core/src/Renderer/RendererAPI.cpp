#include "Renderer/RendererAPI.h"

namespace Core
{
	Configuration::RendererAPI RendererAPI::s_API = CORE_RENDERING_API;

	RendererAPI* RendererAPI::Create()
	{
		switch (CORE_RENDERING_API)
		{
		case Configuration::RendererAPI::OpenGL: //TODO
		case Configuration::RendererAPI::Unknown: CORE_LOG_ERROR("Unknown RendererAPI"); return nullptr;
		}

		CORE_LOG_ERROR("Unknown Rendering API");
		return nullptr;
	}
}
