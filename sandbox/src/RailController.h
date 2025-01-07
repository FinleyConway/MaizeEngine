#pragma once

#include <Maize.h>

#include "Rail.h"

struct RailController
{
    float speed = 8.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;
    Rail::Dir currentDir = Rail::Dir::N;

    RailController() = default;

    RailController(Maize::Vec2f lastPos)
        : lastPos(lastPos), nextPos(lastPos) {}
};
