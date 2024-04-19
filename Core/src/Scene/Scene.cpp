#include "CorePCHeader.h"

#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

namespace Core
{
	Scene::Scene() : m_RegistryCount(0)
	{

	}

	Scene::~Scene()
	{
	}

	void Scene::AddEntity(Entity entity)
	{
		m_Registry.push_back(entity);
		m_ActiveEntity = &m_Registry.back();
		m_ActiveEntity->SetEntityID(m_RegistryCount);
		m_RegistryCount++;
	}

	void Scene::SetSelectedEntity(int id)
	{
		if(&m_Registry[id])
		{
			m_ActiveEntity = &m_Registry[id];
		}
	}

	void Scene::Render(EditorCamera& camera)
	{
		Renderer::BeginScene(camera);

		for (auto entity : m_Registry)
		{
			Renderer::DrawRect(entity.GetTransformComponent().GetTransform(), entity.GetColorComponent().Color, entity.GetEntityID());
		}

		Renderer::EndScene();
	}
}