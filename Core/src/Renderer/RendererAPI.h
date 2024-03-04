#pragma once

#include "Core/Core.h"

namespace Core
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		static Configuration::RendererAPI GetAPI() { return s_API; };
		static RendererAPI* Create();
	private:
		static Configuration::RendererAPI s_API;
	};
}