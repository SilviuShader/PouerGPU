#include "RenderSystem.h"

#include <raylib.h>

#include "../Components/SphereColliderComponent.h"

using namespace entt;

using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	void RenderSystem::RenderColliders(registry& registry)
	{
		Camera camera = { 0 };

		camera.position   = Vector3{ 10.0f, 10.0f, 10.0f };
		camera.target     = Vector3{ 0.0f, 0.0f, 0.0f };   
		camera.up         = Vector3{ 0.0f, 1.0f, 0.0f };   
		camera.fovy       = 45.0f;                         
		camera.projection = CAMERA_PERSPECTIVE;            

		BeginMode3D(camera);
		auto sphereCollidersView = registry.view<const Transform, const SphereColliderComponent>();

		sphereCollidersView.each([](const Transform& transform, const SphereColliderComponent& sphereCollider)
		{
			DrawSphere(transform.translation, sphereCollider.radius * transform.scale.x, GREEN);
		});

		EndMode3D();
	}
}