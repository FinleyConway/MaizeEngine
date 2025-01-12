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

    std::unordered_map<Rail::Type, std::array<Maize::IntRect, 3>> spriteTurns; // temp

    RailController() = default;

    RailController(Maize::Vec2f lastPos, const std::unordered_map<Rail::Type, std::array<Maize::IntRect, 3>>& sprites)
        : lastPos(lastPos), nextPos(lastPos),  spriteTurns(sprites) {}
};
