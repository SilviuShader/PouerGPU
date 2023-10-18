#include "PhysicsSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "../Components/SphereColliderComponent.h"

#include "../Components/RigidbodyComponent.h"

using namespace entt;

using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	void PhysicsSystem::UpdatePhysics(registry& registry, float deltaTime)
	{
		const auto rigidbodyView = registry.view<Transform, RigidbodyComponent>();

		rigidbodyView.each([&](const auto& entity, Transform& transform, RigidbodyComponent& rigidbody)
		{
			if (!rigidbody.isKinematic)
			{
				if (rigidbody.hitInfo.collided)
				{
					auto& hitInfo = rigidbody.hitInfo;

					// TODO: Implement response
					if (SphereColliderComponent* sphereCollider = registry.try_get<SphereColliderComponent>(entity))
					{
						// TODO: Find a nicer way for this transforms
						const auto spherePosition = transform.translation;
						const auto sphereRadius   = transform.scale.x * sphereCollider->radius;
						const auto collisionDist  = Vector3Distance(hitInfo.point, spherePosition);

						transform.translation = Vector3Add(transform.translation, Vector3Scale(hitInfo.normal, (sphereRadius - collisionDist) + EPSILON));
					}

					hitInfo.collided = false;
				}

				if (rigidbody.applyGravity)
					rigidbody.velocity = Vector3Add(rigidbody.velocity, Vector3Scale(rigidbody.gravity, deltaTime));
			}
			transform.translation = Vector3Add(transform.translation, Vector3Scale(rigidbody.velocity, deltaTime));
		});
	}
}