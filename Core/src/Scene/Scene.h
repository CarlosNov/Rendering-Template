#pragma once

#include "Renderer/EditorCamera.h"

namespace Core
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render(EditorCamera& camera);
	};
}