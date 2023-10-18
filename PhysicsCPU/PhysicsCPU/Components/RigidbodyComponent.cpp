#include "RigidbodyComponent.h"

#include <raymath.h>

namespace PhysicsCPU::Components
{
	RigidbodyComponent::RigidbodyComponent() :
		gravity({0.0f, -9.81f, 0.0f}),
		applyGravity(true),
		isKinematic(false),
		velocity(Vector3Zero()),
		angularVelocity(Vector3Zero())
	{
	}
}