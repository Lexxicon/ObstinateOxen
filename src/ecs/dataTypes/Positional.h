#pragma once
#include "ofQuaternion.h"
#include "ofVec3f.h"

struct Transform
{
    ofVec3f Location;
    ofQuaternion Rotation;
};

struct Velocity
{
    ofVec3f Value;
};