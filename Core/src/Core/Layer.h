#pragma once

#include "Core/Core.h"
#include "Events/Event.h"

namespace Core
{
	class CORE_API Layer
	{
	public: 
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() { return m_LayerName; }

	protected:
		std::string m_LayerName;
	};
}