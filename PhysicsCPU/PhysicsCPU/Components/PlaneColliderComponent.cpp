#include "PlaneColliderComponent.h"

namespace PhysicsCPU::Components
{
	PlaneColliderComponent::PlaneColliderComponent() :
		planeUDirection({1.0f, 0.0f, 0.0f}),
		planeVDirection({0.0f, 0.0f, -1.0f}),
		planeSize(10.0f)
	{
	}
}