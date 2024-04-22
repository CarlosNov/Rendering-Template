#pragma once

#include "Renderer/EditorCamera.h"

namespace Core
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate();

		void AddEntity(Entity entity);

		Entity& GetActiveEntity() { return *m_ActiveEntity; };
		void SetActiveEntity(int id);

		Entity& GetEntityByTag(std::string name);
		Entity& GetEntityByID(uint32_t id);

		std::vector<Entity>& GetRegistry() { return m_Registry; };

		void Render(EditorCamera& camera);

	private:
		uint32_t m_RegistryCount;
		std::vector<Entity> m_Registry;
		Entity* m_ActiveEntity;

		friend class Entity;
	};
}