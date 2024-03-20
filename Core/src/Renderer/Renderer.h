#pragma once

#include "Renderer/RendererCommand.h"
#include "Renderer/EditorCamera.h"
#include "Renderer/Shader.h"

namespace Core
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const EditorCamera& camera);
		static void EndScene();

		static void Submit();

		static Configuration::RendererAPI GetAPI() { return RendererAPI::GetAPI(); };
	private:
		uint32_t m_RendererID = 0;
	};
}