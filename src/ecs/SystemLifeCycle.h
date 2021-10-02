#pragma once
#include <functional>

#include "../../lib/flecs.h"

struct LifecycleHandle
{
    std::function<void(flecs::world&)> RegisterTypes;
    std::function<void(flecs::world&)> InitGlobals;
    std::function<void(flecs::world&)> RegisterSystems;
};

template <typename T>
class SystemLifeCycle 
{
public:
    static LifecycleHandle MakeHandle()
    {
        return {
            T::RegisterTypes,
            T::InitGlobals,
            T::RegisterSystems
        };
    }
    
    static void RegisterTypes(flecs::world& ecs) {};
    static void InitGlobals(flecs::world& ecs) {};
    static void RegisterSystems(flecs::world& ecs) {};
};
