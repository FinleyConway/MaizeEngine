#include "MineCarMovement.h"

#include "Grid.h"
#include "RailController.h"

void MineCarMovement::Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (const auto* grid = controller.grid.TryGetComponent<Grid>())
        {
            if (position.ApproxOf(controller.nextPos))
            {
                HandleDirection(*grid, controller, controller.nextPos, controller.lastPos);
            }
        }

        controller.currentTime += controller.speed * s.DeltaTime();
        controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

        const auto lerpPos = controller.lastPos.LerpTo(controller.nextPos, controller.currentTime);
        position.x = lerpPos.x;
        position.y = lerpPos.y;
    }
}

void MineCarMovement::HandleDirection(const Grid& grid, RailController& controller, Maize::Vec2f& nextPosition, Maize::Vec2f& lastPosition)
{
    const Maize::Vec2i gridPos = grid.PixelToCartesian(nextPosition.x, nextPosition.y);
    const auto& tile = grid.Get(gridPos.x, gridPos.y);
    const Maize::Vec2i gridPosOffset = GetDirectionOffset(tile.direction, controller.currentDir, gridPos);

    if (gridPosOffset == Maize::Vec2i(-1, -1)) return;

    const uint8_t nextDirection = grid.Get(gridPosOffset.x, gridPosOffset.y).direction;

    if ((controller.currentDir & nextDirection) == 0) return;

    if (nextDirection != RailType::None)
    {
        lastPosition = nextPosition;
        nextPosition = grid.CartesianToPixel(gridPosOffset.x, gridPosOffset.y);
        controller.currentTime = 0.0f;
    }
}

Maize::Vec2i MineCarMovement::GetDirectionOffset(uint8_t direction, uint8_t& controllerDirection, Maize::Vec2i offset)
{
    switch (direction)
    {
    case RailType::Vertical:   return GetVerticalOffset(controllerDirection, offset);
    case RailType::Horizontal: return GetHorizontalOffset(controllerDirection, offset);
    case RailType::NorthRight: return GetNorthRightOffset(controllerDirection, offset);
    case RailType::NorthLeft:  return GetNorthLeftOffset(controllerDirection, offset);
    case RailType::SouthRight: return GetSouthRightOffset(controllerDirection, offset);
    case RailType::SouthLeft:  return GetSouthLeftOffset(controllerDirection, offset);
    case RailType::None:       return Maize::Vec2i{-1, -1};
    default:                   GAME_ASSERT(false, "Unknown direction");
    }

    return offset;
}

Maize::Vec2i MineCarMovement::CalculateOffsetForDirection(uint8_t& controllerDirection, Maize::Vec2i offset, int deltaX, int deltaY, uint8_t newControllerDirection)
{
    offset.x += deltaX;
    offset.y += deltaY;

    if (newControllerDirection != 0)
    {
        controllerDirection = newControllerDirection;
    }

    return offset;
}

Maize::Vec2i MineCarMovement::GetVerticalOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1);
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1);

    return offset;
}

Maize::Vec2i MineCarMovement::GetHorizontalOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0);

    return offset;
}

Maize::Vec2i MineCarMovement::GetNorthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0, RailDir::E);
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1, RailDir::S);

    return offset;
}

Maize::Vec2i MineCarMovement::GetNorthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0, RailDir::W);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1, RailDir::S);

    return offset;
}

Maize::Vec2i MineCarMovement::GetSouthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0, RailDir::E);
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1, RailDir::N);

    return offset;
}

Maize::Vec2i MineCarMovement::GetSouthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0, RailDir::W);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1, RailDir::N);

    return offset;
}