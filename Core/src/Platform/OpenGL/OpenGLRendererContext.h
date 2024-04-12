#pragma once

#include "Renderer/RendererContext.h"

struct GLFWwindow;

namespace Core
{
	class OpenGLRendererContext : public RendererContext
	{
	public:
		OpenGLRendererContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}