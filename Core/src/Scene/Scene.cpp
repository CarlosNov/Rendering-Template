#include "CorePCHeader.h"

#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

namespace Core
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Render(EditorCamera& camera)
	{
		Renderer::BeginScene(camera);
		Renderer::Submit();
		Renderer::EndScene();
	}
}