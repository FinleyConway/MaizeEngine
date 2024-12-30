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

    Maize::Entity grid;

    RailController() = default;
    RailController(Maize::Vec2f lastPos, Maize::Entity grid)
        : lastPos(lastPos), nextPos(lastPos), grid(grid) {}
};
