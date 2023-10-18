#include <raylib.h>

#include "PhysicsCPU/Core/EntityComponentSystem.h"

#include "PhysicsCPU/Components/SphereColliderComponent.h"

#include "PhysicsCPU/Systems/RenderSystem.h"

using namespace entt;

using namespace PhysicsCPU::Core;
using namespace PhysicsCPU::Components;
using namespace PhysicsCPU::Systems;

int main()
{
	InitWindow(800, 450, "PhysicsCPU");

	SetTargetFPS(60);

	registry registry;

	const auto testSphere = EntityComponentSystem::CreateEntity(registry);
	registry.emplace<SphereColliderComponent>(testSphere);

	while (!WindowShouldClose())
	{
		PollInputEvents();

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("PhysicsCPU", 10, 10, 10, GRAY);

		RenderSystem::RenderColliders(registry);

		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}