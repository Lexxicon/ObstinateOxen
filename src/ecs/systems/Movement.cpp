#include "Movement.h"

#include "../dataTypes/Positional.h"

void Movement::RegisterSystems(flecs::world& ecs)
{
    ecs.system<Transform, const Velocity>("Apply Velocity")
        .each([](Transform& transform, const Velocity& velocity)
        {
            transform.Location += velocity.Value; 
        });
}
