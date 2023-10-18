#pragma once
#include <entt/entt.hpp>

namespace PhysicsCPU::Systems
{
	class PhysicsSystem
	{
	public:

		static void UpdatePhysics(entt::registry&, float);
	};
}
