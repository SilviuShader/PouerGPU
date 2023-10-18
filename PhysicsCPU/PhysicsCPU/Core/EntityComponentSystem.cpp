#include "EntityComponentSystem.h"

#include <raylib.h>
#include <raymath.h>

using namespace entt;

namespace PhysicsCPU::Core
{

    entity EntityComponentSystem::CreateEntity(registry& registry)
    {
        const auto entity = registry.create();

    	Transform t{};
        t.translation = Vector3Zero();
        t.rotation    = QuaternionIdentity();
        t.scale       = Vector3One();

        registry.emplace<Transform>(entity, t);

        return entity;
    }
}
