#pragma once

#include <string_view>

#include "StaticHelperBase.h"

/**
 * Helper class for rail related logic.
 */
class Rail final : public StaticHelperBase
{
public:
    /**
     * Direction layout in binary.
     */
    enum class Dir : uint8_t
    {
        None = 0,	// 00000000
        N    = 1,   // 00000001
        NE   = 2,   // 00000010
        E    = 4,   // 00000100
        SE   = 8,   // 00001000
        S    = 16,  // 00010000
        SW   = 32,  // 00100000
        W    = 64,  // 01000000
        NW   = 128  // 10000000
    };

    /**
     * Bitsets defining the rail type by possible gates.
     */
    enum class Type : uint8_t
    {
        None       = static_cast<uint8_t>(Dir::None),                                // No direction
        Vertical   = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::S),    // (N ↔ S)
        Horizontal = static_cast<uint8_t>(Dir::W) | static_cast<uint8_t>(Dir::E),    // (W ↔ E)

        NorthRight = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::E),    // (N → E | E → N)
        NorthLeft  = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::W),    // (N → W | W → N)
        SouthRight = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::E),    // (S → E | E → S)
        SouthLeft  = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::W),    // (S → W | W → S)

        NESW       = static_cast<uint8_t>(Dir::NE) | static_cast<uint8_t>(Dir::SW),  // (NE → SW | SW → NE)
        NWSE       = static_cast<uint8_t>(Dir::NW) | static_cast<uint8_t>(Dir::SE),  // (NW → SE | SE → NW)
    };

public:
    /**
     * Converts a Direction enum value to its corresponding string representation.
     */
    static std::string_view DirToStr(Dir dir)
    {
        switch (dir)
        {
            case Dir::None: return "None";
            case Dir::N:    return "N";
            case Dir::NE:   return "NE";
            case Dir::E:    return "E";
            case Dir::SE:   return "SE";
            case Dir::S:    return "S";
            case Dir::SW:   return "SW";
            case Dir::W:    return "W";
            case Dir::NW:   return "NW";
            default:        return "Unknown";
        }
    }

    /**
     * Converts a Type enum value to its corresponding string representation.
     */
    static std::string_view TypeToStr(Type type)
    {
        switch (type)
        {
            case Type::None:       return "None";
            case Type::Vertical:   return "Vertical";
            case Type::Horizontal: return "Horizontal";
            case Type::NorthRight: return "North Right";
            case Type::NorthLeft:  return "North Left";
            case Type::SouthRight: return "South Right";
            case Type::SouthLeft:  return "South Left";
            case Type::NESW:       return "NESW";
            case Type::NWSE:       return "NWSE";
            default:               return "Unknown";
        }
    }

    static Type GetType(uint8_t i)
    {
        switch (i)
        {
            case 0: return Type::Vertical;
            case 1: return Type::NorthRight;
            case 2: return Type::Horizontal;
            case 3: return Type::SouthRight;
            case 4: return Type::Vertical;
            case 5: return Type::SouthLeft;
            case 6: return Type::Horizontal;
            case 7: return Type::NorthLeft;
            default: return Type::None;
        }
    }

    /**
     * Check if a tile is curve.
     */
    static bool IsCurve(Type type)
    {
        switch (type)
        {
            case Type::NorthRight: return true;
            case Type::NorthLeft:  return true;
            case Type::SouthRight: return true;
            case Type::SouthLeft:  return true;
            default: return false;
        }
    }

    /**
     * Flip direction to the other side. E.g: N -> S, E -> W
     */
    static Dir FlipDir(Dir dir)
    {
        constexpr uint8_t shift = 4;
        const uint8_t dirByte = static_cast<uint8_t>(dir);
        const uint8_t result = dirByte << shift | dirByte >> shift;

        return static_cast<Dir>(result & 0xFF);
    }

    /**
     * Checks if current traveling direction can travel to a specific rail type.
     */
    static Dir GetNextTravellingDir(Dir direction, Type railType)
    {
        // get the flipped direction byte and rail byte
        const uint8_t dirByte = static_cast<uint8_t>(FlipDir(direction));
        const uint8_t railByte = static_cast<uint8_t>(railType);

        // remove the incoming direction to get the next gate
        const uint8_t nextDirection = railByte - dirByte;

        // check if the next direction is valid or not None
        if (IsValidDirection(nextDirection))
        {
            return static_cast<Dir>(nextDirection);
        }

        return Dir::None;
    }

    /**
     * Get the offset from the given direction.
     */
    static Maize::Vec2i GetDirectionOffset(Dir direction)
    {
        switch (direction)
        {
            case Dir::N:    return Maize::Vec2i(+0, +1);
            case Dir::NE:   return Maize::Vec2i(+1, +1);
            case Dir::E:    return Maize::Vec2i(+1, +0);
            case Dir::SE:   return Maize::Vec2i(+1, -1);
            case Dir::S:    return Maize::Vec2i(+0, -1);
            case Dir::SW:   return Maize::Vec2i(-1, -1);
            case Dir::W:    return Maize::Vec2i(-1, +0);
            case Dir::NW:   return Maize::Vec2i(-1, +1);
            default:        return Maize::Vec2i(+0, +0);
        }
    }

private:
    static bool IsValidDirection(uint8_t value)
    {
        switch (static_cast<Dir>(value))
        {
            case Dir::N:
            case Dir::NE:
            case Dir::E:
            case Dir::SE:
            case Dir::S:
            case Dir::SW:
            case Dir::W:
            case Dir::NW:
                return true;
            default:
                return false;
        }
    }
};