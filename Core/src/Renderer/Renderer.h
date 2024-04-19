#pragma once

#include "Renderer/RendererCommand.h"
#include "Renderer/EditorCamera.h"
#include "Renderer/Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

		static void StartBatch();
		static void Flush();

		static void DrawRect(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color);
		static void DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);

		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, uint32_t entityID = -1);

		static Configuration::RendererAPI GetAPI() { return RendererAPI::GetAPI(); };
	private:
		uint32_t m_RendererID = 0;
	};
}