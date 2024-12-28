#pragma once

#include <cstdint>
#include <string_view>

/**
 * Direction layout in binary.
 */
namespace RailDir
{
    enum
    {
        None = 0, // 00000000
        N    = 1, // 00000001
        E    = 2, // 00000010
        S    = 4, // 00000100
        W    = 8, // 00001000
    };

    inline std::string_view RailDirToStr(uint8_t dir)
    {
        switch (dir)
        {
        case None: return "None";
        case N:    return "N";
        case E:    return "E";
        case S:    return "S";
        case W:    return "W";
        default:   return "Unknown";
        }
    }
} // RailDir

/**
 * Bitsets that defines the rail type by possible i/o.
 */
namespace RailType
{
    enum
    {
        None       = RailDir::None,            // No direction (00000000)

        Vertical   = RailDir::N  | RailDir::S, // (i: north, o: south) | (i: south, o: north) (00000101)
        Horizontal = RailDir::W  | RailDir::E, // (i: west,  o: east)  | (i: east,  o: west)  (00001010)

        NorthRight = RailDir::N  | RailDir::E, // (i: north, o: east)  | (i: east,  o: south) (00000011)
        NorthLeft  = RailDir::N  | RailDir::W, // (i: north, o: west)  | (i: west,  o: south) (00001001)

        SouthRight = RailDir::S  | RailDir::E, // (i: south, o: east)  | (i: east,  o: north) (00000110)
        SouthLeft  = RailDir::S  | RailDir::W, // (i: south, o: west)  | (i: west,  o: north) (00001100)
    };

    inline std::string_view RailTypeToStr(uint8_t type)
    {
        switch (type)
        {
        case None:       return "None";
        case Vertical:   return "Vertical";
        case Horizontal: return "Horizontal";
        case NorthRight: return "North Right";
        case NorthLeft:  return "North Left";
        case SouthRight: return "South Right";
        case SouthLeft:  return "South Left";
        default:         return "Unknown";
        }
    }
} // RailType
