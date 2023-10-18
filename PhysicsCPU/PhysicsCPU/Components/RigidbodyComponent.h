#pragma once

#include <raylib.h>

namespace PhysicsCPU::Components
{
	struct HitInfo
	{
		Vector3 point;
		Vector3 normal;
		bool    collided;

		HitInfo();
	};

	struct RigidbodyComponent
	{
		Vector3 gravity;
		bool    applyGravity;
		bool    isKinematic;

		Vector3 velocity;
		Vector3 angularVelocity;

		HitInfo hitInfo;

		RigidbodyComponent();
	};
}
