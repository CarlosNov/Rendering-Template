#include "Platform/OpenGL/OpenGLRendererContext.h"

#include "CorePCHeader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
	OpenGLRendererContext::OpenGLRendererContext(GLFWwindow* window) : m_Window(window)
	{
		CORE_ASSERT(window, "The window is null!");
	}

	void OpenGLRendererContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Error initialazing GLAD.");

		CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "It is required at least OpenGL version 4.5!");
	}

	void OpenGLRendererContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}