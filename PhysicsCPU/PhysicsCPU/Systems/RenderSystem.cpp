#include "RenderSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "../Components/PlaneColliderComponent.h"
#include "../Components/SphereColliderComponent.h"

using namespace entt;
using namespace PhysicsCPU::Components;

namespace PhysicsCPU::Systems
{
	Model RenderSystem::planeModel = Model();

	void RenderSystem::InitializeResources()
	{
		constexpr auto planeSize       = 1.0f;
		constexpr auto planeResolution = 32;

		planeModel = LoadModelFromMesh(GenMeshPlane(planeSize, planeSize, planeResolution, planeResolution));
	}

	void RenderSystem::RenderColliders(registry& registry)
	{
		auto planeCollidersView  = registry.view<const Transform, const PlaneColliderComponent>();
		auto sphereCollidersView = registry.view<const Transform, const SphereColliderComponent>();

		Camera camera;

		camera.position   = Vector3{ 10.0f, 10.0f, 10.0f };
		camera.target     = Vector3{ 0.0f, 0.0f, 0.0f };   
		camera.up         = Vector3{ 0.0f, 1.0f, 0.0f };   
		camera.fovy       = 45.0f;                         
		camera.projection = CAMERA_PERSPECTIVE;            

		BeginMode3D(camera);

		planeCollidersView.each([](const Transform& transform, const PlaneColliderComponent& planeCollider)
		{
			const Vector3    defaultPlaneUp = { 0.0f, 1.0f, 0.0f };
			const Vector3    planeUp        = Vector3Normalize(Vector3CrossProduct(planeCollider.planeUDirection, planeCollider.planeVDirection));
			const Quaternion deltaRotation  = QuaternionFromVector3ToVector3(defaultPlaneUp, planeUp);
			const Quaternion planeRotation  = QuaternionMultiply(deltaRotation, transform.rotation);

			Vector3 rotationAxis;
			float   rotationAngle;
			QuaternionToAxisAngle(planeRotation, &rotationAxis, &rotationAngle);

			auto planeColor = GRAY;
			planeColor.a = 128;

			DrawModelEx(planeModel, transform.translation, rotationAxis, rotationAngle * RAD2DEG, Vector3Scale(transform.scale, planeCollider.planeSize), planeColor);
		});

		sphereCollidersView.each([](const auto& transform, const auto& sphereCollider)
		{
			DrawSphere(transform.translation, sphereCollider.radius * transform.scale.x, GREEN);
		});

		EndMode3D();
	}

	void RenderSystem::FreeResources()
	{
		UnloadModel(planeModel);
	}
}