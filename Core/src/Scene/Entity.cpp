#include "CorePCHeader.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"


namespace Core
{
	Entity::Entity(Scene* scene) : m_Scene(scene)
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::OnInit()
	{

	}

	void Entity::OnUpdate()
	{
		if (m_ScriptComponent.Initialized)
		{
			m_ScriptComponent.velocity += glm::vec2(0.0f, -1.0f) * m_ScriptComponent.gravity;
			m_TransformComponent.Translation += glm::vec3(m_ScriptComponent.velocity.x, m_ScriptComponent.velocity.y, 0.0f);

			Entity entityUp = m_Scene->GetEntityByTag("Bound Down");
			Entity entityDown = m_Scene->GetEntityByTag("Bound Up");
			Entity entityRight = m_Scene->GetEntityByTag("Bound Right");
			Entity entityLeft = m_Scene->GetEntityByTag("Bound Left");

			float upY = abs(entityUp.GetTransformComponent().Translation.y);
			float downY = abs(entityDown.GetTransformComponent().Translation.y);
			float rightX = abs(entityRight.GetTransformComponent().Translation.x);
			float leftX = abs(entityLeft.GetTransformComponent().Translation.x);
			float upBorderSize = abs(entityUp.GetTransformComponent().Scale.y);
			float downBorderSize = abs(entityDown.GetTransformComponent().Scale.y);
			float sizeX = m_TransformComponent.Scale.x;
			float sizeY = m_TransformComponent.Scale.y;

			glm::vec2 halfBoundsSize = glm::vec2(rightX + leftX, upY + downY + (0.5f - upBorderSize) + (0.5f - downBorderSize)) / 2.0f - glm::vec2(1.0f, 1.0f) * glm::vec2(sizeX, sizeY);

			if (abs(m_TransformComponent.Translation.x) > halfBoundsSize.x)
			{
				float sign = std::signbit(m_TransformComponent.Translation.x) ? -1 : 1;
				m_TransformComponent.Translation.x = halfBoundsSize.x * sign;
				m_ScriptComponent.velocity.x *= -1;
			}

			LOG_INFO("TRACE: {0} - {1}", abs(m_TransformComponent.Translation.y), halfBoundsSize.y);
			if (abs(m_TransformComponent.Translation.y) > halfBoundsSize.y)
			{
				float sign = std::signbit(m_TransformComponent.Translation.y) ? -1 : 1;
				m_TransformComponent.Translation.y = halfBoundsSize.y * sign;
				m_ScriptComponent.velocity.y *= -1;
			}
		}
	}
}