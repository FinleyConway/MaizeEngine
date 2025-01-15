#pragma once

#include <Maize.h>

#include "Rail.h"

struct RailController
{
    float speed = 2.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;

    Rail::Dir travellingDirection = Rail::Dir::N;
    Rail::Type nextRail = Rail::Type::None;
    bool isTurning = false;
    float turningTime = 0.0f;

    RailController() = default;

    RailController(Maize::Vec2f lastPos)
        : lastPos(lastPos), nextPos(lastPos) {}
};
