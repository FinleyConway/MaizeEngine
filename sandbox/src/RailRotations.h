#pragma once

#include <Maize.h>

#include "Rail.h"

struct RailRotations
{
public:
    std::vector<Maize::IntRect> rotations;

public:
    RailRotations() = default;

    RailRotations(const std::vector<Maize::IntRect>& rotations) : rotations(rotations) {}

    Maize::IntRect GetRotationSprite(size_t index) const
    {
        if (index > rotations.size() || rotations.empty()) return Maize::IntRect();

        return rotations[index];
    }

    size_t GetDirectionIndex(Rail::Dir direction) const
    {
        constexpr uint8_t rotationOffset = 16;

        switch (direction)
        {
        case Rail::Dir::N:    return 0 * rotationOffset;
        case Rail::Dir::NE:   return 1 * rotationOffset - 1;
        case Rail::Dir::E:    return 2 * rotationOffset - 1;
        case Rail::Dir::SE:   return 3 * rotationOffset - 1;
        case Rail::Dir::S:    return 4 * rotationOffset - 1;
        case Rail::Dir::SW:   return 5 * rotationOffset - 1;
        case Rail::Dir::W:    return 6 * rotationOffset - 1;
        case Rail::Dir::NW:   return 7 * rotationOffset - 1;
        default:              return 0 * rotationOffset - 1;
        }
    }
};