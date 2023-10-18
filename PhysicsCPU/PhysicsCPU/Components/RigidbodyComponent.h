#pragma once

#include <raylib.h>

namespace PhysicsCPU::Components
{
	struct RigidbodyComponent
	{
		Vector3 gravity;
		bool    applyGravity;
		bool    isKinematic;

		Vector3 velocity;
		Vector3 angularVelocity;

		RigidbodyComponent();
	};
}
