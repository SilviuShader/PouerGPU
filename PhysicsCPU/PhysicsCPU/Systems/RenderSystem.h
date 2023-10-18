#pragma once
#include <raylib.h>
#include <entt/entt.hpp>

namespace PhysicsCPU::Systems
{
	class RenderSystem
	{
	public:

		static void InitializeResources();
		static void RenderColliders(entt::registry&);
		static void FreeResources();

	private:

		static Model planeModel;
	};
}
