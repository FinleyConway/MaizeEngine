#pragma once

#include <Maize.h>

#include "RailTypes.h"

struct RailController
{
    float speed = 8.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;
    uint8_t currentDir = RailDir::N;

    Maize::Entity grid;

    RailController() = default;
    RailController(Maize::Vec2f lastPos, Maize::Entity grid)
        : lastPos(lastPos), nextPos(lastPos), grid(grid) {}
};
