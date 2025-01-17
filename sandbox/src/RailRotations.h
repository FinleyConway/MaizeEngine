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

    size_t GetDirectionIndex(Rail::Dir direction, bool wrap = false, uint16_t offset = 4) const
    {
        if (wrap) return 8 * offset - 1;

        switch (direction)
        {
            case Rail::Dir::N:    return 0 * offset;
            case Rail::Dir::NE:   return 1 * offset - 1;
            case Rail::Dir::E:    return 2 * offset - 1;
            case Rail::Dir::SE:   return 3 * offset - 1;
            case Rail::Dir::S:    return 4 * offset - 1;
            case Rail::Dir::SW:   return 5 * offset - 1;
            case Rail::Dir::W:    return 6 * offset - 1;
            case Rail::Dir::NW:   return 7 * offset - 1;
            default:              return 0 * offset;
        }
    }

    std::pair<size_t, size_t> GetRotations(Rail::Dir currentDir, Rail::Type railType) const
    {
        const auto direction = Rail::GetNextTravellingDir(currentDir, railType);
        const size_t from = GetDirectionIndex(currentDir);
        const size_t to = GetDirectionIndex(direction, currentDir == Rail::Dir::W && direction == Rail::Dir::N);

        return { from, to };
    }
};