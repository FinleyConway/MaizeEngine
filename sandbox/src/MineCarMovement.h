#pragma once

#include <Maize.h>

struct Grid;
struct RailController;

class MineCarMovement
{
public:
    static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller);

private:
    static void HandleDirection(const Grid& grid, RailController& controller, Maize::Vec2f& nextPosition, Maize::Vec2f& lastPosition);

    static Maize::Vec2i GetDirectionOffset(uint8_t direction, uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i CalculateOffsetForDirection(uint8_t& controllerDirection, Maize::Vec2i offset, int deltaX, int deltaY, uint8_t newControllerDirection = 0);

    static Maize::Vec2i GetVerticalOffset(uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i GetHorizontalOffset(uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i GetNorthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i GetNorthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i GetSouthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset);

    static Maize::Vec2i GetSouthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset);
};
