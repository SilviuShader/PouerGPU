#include "RigidbodyComponent.h"

#include <raymath.h>

namespace PhysicsCPU::Components
{
	HitInfo::HitInfo() :
		point(Vector3Zero()),
		normal(Vector3Zero()),
		collided(false)
	{
	}

	RigidbodyComponent::RigidbodyComponent() :
		gravity({0.0f, -9.81f, 0.0f}),
		applyGravity(true),
		isKinematic(false),
		velocity(Vector3Zero()),
		angularVelocity(Vector3Zero()),
		hitInfo(HitInfo())
	{
	}
}