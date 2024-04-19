#pragma once

#include "Scene/Components.h"

namespace Core
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other) = default;
		~Entity();

		void OnInit();
		void OnUpdate();

		TransformComponent& GetTransformComponent() { return transformComponent; };
		void SetTransformComponent(TransformComponent transform) { transformComponent = transform; };

		ColorComponent& GetColorComponent() { return colorComponent; };
		void SetColorComponent(ColorComponent color) { colorComponent = color; };

		int GetEntityID() { return m_EntityID; };
		void SetEntityID(int id) { m_EntityID = id; };

	private:
		TransformComponent transformComponent;
		ColorComponent colorComponent;
		int m_EntityID;
	};
}