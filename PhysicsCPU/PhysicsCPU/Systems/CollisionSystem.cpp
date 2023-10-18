#include "CollisionSystem.h"

#include <iostream>

#include <raylib.h>
#include <raymath.h>

#include "../Components/PlaneColliderComponent.h"
#include "../Components/SphereColliderComponent.h"

#include "../Components/RigidbodyComponent.h"

using namespace std;

using namespace entt;

using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	void CollisionSystem::EvaluateCollisions(registry& registry)
	{
		const auto planesView  = registry.view<Transform, PlaneColliderComponent>();
		const auto spheresView = registry.view<Transform, SphereColliderComponent>();

		// TODO: Clean up and make functions for things that repeat (like getting the rigidbody of an object, or handling the scale of objects)
		// TODO: Sphere vs sphere collision..
		planesView.each([&](const auto& planeEntity, Transform& planeTransform, PlaneColliderComponent& planeCollider)
		{
			const auto planeOrigin     = planeTransform.translation;

			const auto planeUDirection = Vector3Normalize(Vector3RotateByQuaternion(planeCollider.planeUDirection, planeTransform.rotation));
			const auto planeVDirection = Vector3Normalize(Vector3RotateByQuaternion(planeCollider.planeVDirection, planeTransform.rotation));
			const auto planeNormal     = Vector3Normalize(Vector3CrossProduct(planeUDirection, planeVDirection));

			const auto planeUSize      = planeCollider.planeSize * planeTransform.scale.x;
			const auto planeVSize      = planeCollider.planeSize * planeTransform.scale.z;

			spheresView.each([&](const auto& sphereEntity, Transform& sphereTransform, SphereColliderComponent& sphereCollider)
			{
				const auto spherePosition = sphereTransform.translation;
				const auto sphereRadius   = sphereTransform.scale.x * sphereCollider.radius;

				const auto toPlane     = Vector3Subtract(spherePosition, planeOrigin);
				const auto uProjection = Vector3DotProduct(toPlane, planeUDirection);
				const auto vProjection = Vector3DotProduct(toPlane, planeVDirection);

				if (uProjection <= planeUSize && vProjection <= planeVSize)
				{
					const auto normalProjection = Vector3DotProduct(toPlane, planeNormal);
					if (fabsf(normalProjection) <= sphereRadius)
					{
						HitInfo sphereHitInfo;
						sphereHitInfo.point    = Vector3Subtract(spherePosition, Vector3Scale(planeNormal, normalProjection));
						sphereHitInfo.normal   = Vector3Normalize(Vector3Subtract(spherePosition, sphereHitInfo.point));
						sphereHitInfo.collided = true;

						HitInfo planeHitInfo = sphereHitInfo;
						planeHitInfo.normal = Vector3Scale(planeHitInfo.normal, -1.0f);

						if (RigidbodyComponent* planeRigidbody = registry.try_get<RigidbodyComponent>(planeEntity))
							if (!planeRigidbody->isKinematic)
								planeRigidbody->hitInfo = planeHitInfo;

						if (RigidbodyComponent* sphereRigidbody = registry.try_get<RigidbodyComponent>(sphereEntity))
							if (!sphereRigidbody->isKinematic)
								sphereRigidbody->hitInfo = sphereHitInfo;
					}
				}
			});
		});
	}
}