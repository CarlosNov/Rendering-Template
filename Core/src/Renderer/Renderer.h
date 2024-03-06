#pragma once

#include "Renderer/RendererAPI.h"

namespace Core
{
	class Renderer
	{
	public:
		static Configuration::RendererAPI GetAPI() { return RendererAPI::GetAPI(); };
	};
}