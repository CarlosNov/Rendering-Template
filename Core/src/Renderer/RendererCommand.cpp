#include "Renderer/RendererCommand.h"

namespace Core
{
	std::unique_ptr<RendererAPI> RendererCommand::s_RendererAPI(RendererAPI::Create());
}
