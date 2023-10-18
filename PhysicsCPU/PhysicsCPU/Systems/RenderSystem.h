#pragma once
#include <entt/entt.hpp>

namespace PhysicsCPU::Systems
{
	class RenderSystem
	{
	public:

		static void RenderColliders(entt::registry&);
	};
}
