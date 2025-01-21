#pragma once

#include "Rail.h"

struct FuzzyShape
{
    uint8_t shape = 0;
    uint8_t mask = 0;
    std::array<Rail::Type, 9> quadrants;

    FuzzyShape() = default;

    FuzzyShape(uint8_t shape, uint8_t mask, std::array<Rail::Type, 9>&& quadrants)
        : shape(shape), mask(mask), quadrants(std::move(quadrants))
    {

    }

    Rail::Type GetType(uint8_t x, uint8_t y) const
    {
        // out of bounds
        if (x > 2 || y > 2) return Rail::Type::None;

        return quadrants[x + y * 3];
    }

    bool Match(uint8_t bitset) const
    {
        return (shape & mask) == (bitset & mask);
    }

    bool operator==(const FuzzyShape& other) const
    {
        return (shape & mask) == (other.shape & other.mask);
    }
};
