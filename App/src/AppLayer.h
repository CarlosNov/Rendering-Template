#pragma once

#include "CoreHeader.h"

#include "Renderer/EditorCamera.h"
#include "Renderer/Framebuffer.h"

#include "Events/MouseEvent.h"
#include "Events/Event.h"

#include "Panels/SceneHierarchyPanel.h"

namespace App
{
	class AppLayer : public Core::Layer
	{
	public:
		AppLayer();
		virtual ~AppLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Core::Event& event) override;

	private:
		bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& e);
	private:

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		Core::EditorCamera m_EditorCamera;
		Core::Framebuffer* m_Framebuffer;

		Core::Scene  m_ActiveScene;
		Core::Entity m_HoveredEntity;

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}
