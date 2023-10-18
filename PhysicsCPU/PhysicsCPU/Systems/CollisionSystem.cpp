#include "CollisionSystem.h"

#include <iostream>

#include <raylib.h>
#include <raymath.h>

#include "../Components/PlaneColliderComponent.h"
#include "../Components/SphereColliderComponent.h"

using namespace std;

using namespace entt;

using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	void CollisionSystem::EvaluateCollisions(registry& registry)
	{
		const auto planesView  = registry.view<Transform, PlaneColliderComponent>();
		const auto spheresView = registry.view<Transform, SphereColliderComponent>();

		planesView.each([&](Transform& planeTransform, PlaneColliderComponent& planeCollider)
		{
			const auto planeOrigin     = planeTransform.translation;

			const auto planeUDirection = Vector3Normalize(Vector3RotateByQuaternion(planeCollider.planeUDirection, planeTransform.rotation));
			const auto planeVDirection = Vector3Normalize(Vector3RotateByQuaternion(planeCollider.planeVDirection, planeTransform.rotation));
			const auto planeNormal     = Vector3Normalize(Vector3CrossProduct(planeUDirection, planeVDirection));

			const auto planeUSize      = planeCollider.planeSize * planeTransform.scale.x;
			const auto planeVSize      = planeCollider.planeSize * planeTransform.scale.z;

			spheresView.each([&](Transform& sphereTransform, SphereColliderComponent& sphereCollider)
			{
				const auto spherePosition = sphereTransform.translation;
				const auto sphereRadius   = sphereTransform.scale.x * sphereCollider.radius;
				const auto sphereRadiusSq = sphereRadius * sphereRadius;

				const auto toPlane     = Vector3Subtract(spherePosition, planeOrigin);
				const auto uProjection = Vector3DotProduct(toPlane, planeUDirection);
				const auto vProjection = Vector3DotProduct(toPlane, planeVDirection);

				if (uProjection <= planeUSize && vProjection <= planeVSize)
				{
					const auto normalProjection = Vector3DotProduct(toPlane, planeNormal);
					const auto lengthSq = normalProjection * normalProjection;
					if (lengthSq <= sphereRadiusSq)
						cout << "PLANE VS SPHERE COLLISION" << endl;
				}
			});
		});
	}
}