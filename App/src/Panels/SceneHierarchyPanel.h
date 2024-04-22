#pragma once

#include "CoreHeader.h"

#include "Renderer/EditorCamera.h"
#include "Renderer/Framebuffer.h"

#include "Events/MouseEvent.h"
#include "Events/Event.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace App
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;

		void SetScene(Core::Scene* scene);

		void OnImGuiRender();

	private:
		void DrawSceneNode();
		void DrawEntityNode(Core::Entity& entity);
		void DrawComponents(Core::Entity& entity);

		template<typename T, typename F>
		void DrawComponent(const std::string& name, Core::Entity& entity, F function);

		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);
	private:
		Core::Scene* m_Scene;
		Core::Entity m_SelectedEntity;
		uint32_t m_SelectedNode;
	};
}
