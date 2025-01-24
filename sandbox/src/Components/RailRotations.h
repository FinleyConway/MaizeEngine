#pragma once

#include "Utils/RailTurnDirection.h"

struct RailRotations
{
public:
    std::vector<RailTurnDirection> rotations;

    RailRotations() = default;

    RailRotations(const std::vector<RailTurnDirection>& rotations) : rotations(rotations) {}
};
