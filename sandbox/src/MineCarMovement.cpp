/*#include "MineCarMovement.h"

#include "Grid.h"
#include "RailController.h"

void MineCarMovement::Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (const auto* grid = controller.grid.TryGetComponent<Grid<RailTile>>())
        {
            if (position.ApproxOf(controller.nextPos))
            {
                HandleDirection(*grid, controller);
            }
        }

        controller.currentTime += controller.speed * s.DeltaTime();
        controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

        position = controller.lastPos.LerpTo(controller.nextPos, controller.currentTime);
    }
}

void MineCarMovement::HandleDirection(const Grid<RailTile>& grid, RailController& controller)
{
    // get the current tile check if it's within the grid.
    const Maize::Vec2i gridPos = grid.PixelToCartesian(controller.nextPos.x, controller.nextPos.y);

    if (grid.IsWithin(gridPos.x, gridPos.y))
    {
        // get the tile and find what the next direction is based on the travelling direction
        const auto& tile = grid.Get(gridPos.x, gridPos.y);
        const auto nextDirection = Rail::GetNextTravellingDir(controller.currentDir, tile.railType);

        GAME_LOG_INFO("Current Rail Dir is {}", Rail::TypeToStr(tile.railType));

        // don't find the next tile if its no rail.
        if (nextDirection != Rail::Dir::None)
        {
            // get the next tile
            const auto directionOffset = Rail::GetDirectionOffset(nextDirection);
            const auto offset = directionOffset + gridPos;

            // assign the next rail destination if it's within the grid.
            if (grid.IsWithin(offset.x, offset.y))
            {
                controller.lastPos = controller.nextPos;
                controller.nextPos = grid.CartesianToPixel(offset.x, offset.y);
                controller.currentTime = 0.0f;
                controller.currentDir = nextDirection;

                GAME_LOG_INFO("Offset: [{}, {}]", offset.x, offset.y);
                GAME_LOG_INFO("Current direction is {}", Rail::DirToStr(nextDirection));
            }
        }
    }
}*/