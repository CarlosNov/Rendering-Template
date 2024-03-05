#pragma once

#include "CoreHeader.h"

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
		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}
