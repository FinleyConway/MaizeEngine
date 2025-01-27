#pragma once

#include "Utils/Rail.h"

class FuzzyShape
{
public:
    FuzzyShape(uint8_t shape, uint8_t mask, std::array<Rail::Type, 9>&& quadrants)
        : m_Shape(shape), m_Mask(mask), m_Quadrants(std::move(quadrants))
    {
    }

    Rail::Type GetType(uint8_t x, uint8_t y) const
    {
        // out of bounds
        if (x > 2 || y > 2) return Rail::Type::None;

        return m_Quadrants[x + y * 3];
    }

    bool Match(uint8_t bitset) const
    {
        return (m_Shape & m_Mask) == (bitset & m_Mask);
    }

    bool operator==(const FuzzyShape& other) const
    {
        return (m_Shape & m_Mask) == (other.m_Shape & other.m_Mask);
    }

private:
    uint8_t m_Shape = 0;
    uint8_t m_Mask = 0;
    std::array<Rail::Type, 9> m_Quadrants;
};
