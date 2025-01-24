#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

struct RailRotations
{
public:
    std::vector<Maize::IntRect> rotations;

public:
    RailRotations() = default;

    RailRotations(const std::vector<Maize::IntRect>& rotations) : rotations(rotations) {}

    size_t GetDirectionIndex(Rail::Dir direction) const
    {
        switch (direction)
        {
            case Rail::Dir::N: return 1;
            case Rail::Dir::E: return 2;
            case Rail::Dir::S: return 4;
            case Rail::Dir::W: return 6;
            default:           return 0;
        }
    }
};
