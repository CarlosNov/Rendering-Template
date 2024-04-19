#pragma once

#include "Renderer/EditorCamera.h"

#include "Scene/Entity.h"

namespace Core
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void AddEntity(Entity entity);
		Entity& GetActiveEntity() { return *m_ActiveEntity; }
		void SetSelectedEntity(int id);

		void Render(EditorCamera& camera);

	private:
		uint32_t m_RegistryCount;
		std::vector<Entity> m_Registry;
		Entity* m_ActiveEntity;
	};
}