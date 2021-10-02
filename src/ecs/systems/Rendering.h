#pragma once
#include "../SystemLifeCycle.h"
#include "../../../lib/flecs.h"

class Rendering : public SystemLifeCycle<Rendering>
{
public:
    static void RegisterTypes(flecs::world& ecs);
    static void InitGlobals(flecs::world& ecs);
    static void RegisterSystems(flecs::world& ecs);
};
