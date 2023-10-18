#pragma once
#include <raylib.h>

namespace PhysicsCPU::Components
{
	class PlaneColliderComponent
	{
	public:

		Vector3 planeUDirection;
		Vector3 planeVDirection;
		float   planeSize;

		PlaneColliderComponent();
	};
}
