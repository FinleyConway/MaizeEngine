#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

class RailTurnDirection;

struct RailController
{
    float speed = 5.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;
    bool isMoving = false;

    Rail::Dir travellingDirection = Rail::Dir::N;
    Rail::Dir nextDirection = Rail::Dir::N;
    Rail::Type nextRail = Rail::Type::Vertical;

    bool isTurning = false;
    float turningTime = 0.0f;
    const RailTurnDirection* currentRotations = nullptr;
    Rail::Dir currentRotateDirection = Rail::Dir::None;

    RailController() = default;

    RailController(Maize::Vec2f lastPos)
        : lastPos(lastPos), nextPos(lastPos) {}
};
