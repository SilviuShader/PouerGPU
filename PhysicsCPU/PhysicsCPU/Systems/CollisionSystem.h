#pragma once
#include <entt/entt.hpp>

namespace PhysicsCPU::Systems
{
	class CollisionSystem
	{
	public:

		static void EvaluateCollisions(entt::registry&);
	};
}
