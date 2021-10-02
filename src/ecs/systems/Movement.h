#pragma once
#include "../SystemLifeCycle.h"

class Movement : public SystemLifeCycle<Movement>
{
public:
    static void RegisterSystems(flecs::world& ecs);
};
