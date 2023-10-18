#pragma once

#include <entt/entt.hpp>

namespace PhysicsCPU::Core
{
	class EntityComponentSystem
	{
	public:

		static entt::entity CreateEntity(entt::registry&);
	};
}