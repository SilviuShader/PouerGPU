#include "PhysicsSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "../Components/RigidbodyComponent.h"

using namespace entt;

using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	void PhysicsSystem::UpdatePhysics(registry& registry, float deltaTime)
	{
		const auto rigidbodyView = registry.view<Transform, RigidbodyComponent>();

		rigidbodyView.each([&](auto& transform, auto& rigidbody)
		{
			if (!rigidbody.isKinematic && rigidbody.applyGravity)
				rigidbody.velocity = Vector3Add(rigidbody.velocity, Vector3Scale(rigidbody.gravity, deltaTime));

			transform.translation = Vector3Add(transform.translation, Vector3Scale(rigidbody.velocity, deltaTime));
		});
	}
}