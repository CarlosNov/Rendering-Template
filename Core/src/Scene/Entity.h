#pragma once

#include "Scene/Components.h"

namespace Core
{
	class Scene;

	class Entity
	{
	public:
		Entity() = default;
		Entity(Scene* scene);
		~Entity();

		void OnInit();
		void OnUpdate();

		TagComponent& GetTagComponent() { return m_TagComponent; };
		void SetTagComponent(TagComponent tag) { m_TagComponent = tag; };

		TransformComponent& GetTransformComponent() { return m_TransformComponent; };
		void SetTransformComponent(TransformComponent transform) { m_TransformComponent = transform; };

		ColorComponent& GetColorComponent() { return m_ColorComponent; };
		void SetColorComponent(ColorComponent color) { m_ColorComponent = color; };

		ScriptComponent& GetScriptComponent() { return m_ScriptComponent; };
		void SetScriptComponent(ScriptComponent script) { m_ScriptComponent = script; };

		int GetEntityID() { return m_EntityID; };
		void SetEntityID(int id) { m_EntityID = id; };

		bool HasTagComponent() { return m_TagComponent.Tag != ""; };
		bool HasScriptComponent() { return m_ScriptComponent.Initialized; };

		operator bool() const
		{
			return m_EntityID != -1;
		}

		bool operator==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;
		}

	private:
		TagComponent m_TagComponent;
		TransformComponent m_TransformComponent;
		ColorComponent m_ColorComponent;
		ScriptComponent m_ScriptComponent;

		Scene* m_Scene = nullptr;
		int m_EntityID = -1;
	};
}