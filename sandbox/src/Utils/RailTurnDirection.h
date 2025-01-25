#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

class RailTurnDirection
{
public:
    RailTurnDirection(Rail::DirBits directions, Rail::DirBits reversedDirections, std::vector<Maize::IntRect>&& rotations):
        m_Directions(directions), m_ReverseDirections(reversedDirections),  m_Rotations(std::move(rotations))
    {
    }

    bool DoesMatchDirection(Rail::Dir currentDirection, Rail::Type nextRail) const
    {
        const auto currentDirectionBits = Rail::ToBitset(currentDirection);

        // check if current direction matches any valid direction or reverse direction
        if (currentDirectionBits & (m_Directions | m_ReverseDirections))
        {
            const Rail::DirBits railBits = Rail::ToBitset(Rail::GetNextTravellingDir(currentDirection, nextRail));

            // check if the next rail will lead to these rotations.
            return (m_Directions & railBits) || (m_ReverseDirections & railBits);
        }

        return false;
    }

    const Maize::IntRect& GetRotation(Rail::Dir nextDirection, size_t index) const
    {
        GAME_ASSERT(index < m_Rotations.size(), "Rotation index out of bounds.");

        if (ShouldReverse(nextDirection))
        {
            return m_Rotations[(m_Rotations.size() - 1) - index];
        }

        return m_Rotations[index];
    }

    size_t GetNumberOfRotations() const
    {
        return m_Rotations.size() - 1;
    }

private:
    bool ShouldReverse(Rail::Dir nextDirection) const
    {
        // check if this direction overlaps with any of the reversed directions
        return Rail::ToBitset(nextDirection) & m_ReverseDirections;
    }

private:
    Rail::DirBits m_Directions = 0;
    Rail::DirBits m_ReverseDirections = 0;
    std::vector<Maize::IntRect> m_Rotations;
};
