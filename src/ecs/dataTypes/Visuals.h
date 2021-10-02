#pragma once
#include "ofColor.h"

struct RenderPhases
{
    struct Background{};
    struct PreDraw{};
    struct Draw{};
    struct PostDraw{};

    flecs::query<> Pipeline;
};

struct Circle
{
    ofColor Color;
    float Radius;
};