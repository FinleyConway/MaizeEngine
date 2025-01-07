#include "MineCarMovement.h"

#include "ChunkManager.h"
#include "Grid.h"
#include "GridConversion.h"
#include "RailController.h"

void MineCarMovement::Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();
    const auto* chunkManager = s.GetSingleton<ChunkManager>();

    GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (position.ApproxOf(controller.nextPos))
        {
            HandleDirection(chunkManager, controller);
        }

        controller.currentTime += controller.speed * s.DeltaTime();
        controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

        position = controller.lastPos.LerpTo(controller.nextPos, controller.currentTime);
    }
}

void MineCarMovement::HandleDirection(const ChunkManager* chunkManager, RailController& controller)
{
    // get the current tile check if it's within the grid.
    const auto gridPosition = GridConversion::PixelToCartesian(controller.nextPos, chunkManager->cellSize);
    const auto chunkPosition = GridConversion::CartesianToChunk(gridPosition, chunkManager->chunkSize);
    const auto entity = chunkManager->TryGetChunk(chunkPosition);

    if (const auto* grid = entity.TryGetComponent<Grid<RailTile>>())
    {
        // get the tile and find what the next direction is based on the travelling direction
        const auto localPosition = GridConversion::CartesianToChunkLocal(gridPosition, chunkManager->chunkSize);
        const auto& tile = grid->Get(localPosition, chunkManager->chunkSize);
        const auto nextDirection = Rail::GetNextTravellingDir(controller.currentDir, tile.railType);

        // don't find the next tile if its no rail.
        if (nextDirection != Rail::Dir::None)
        {
            // get the next tile
            const auto directionOffset = Rail::GetDirectionOffset(nextDirection);
            const auto offset = directionOffset + gridPosition;
            const auto nextPosition = GridConversion::CartesianToPixel(offset, chunkManager->cellSize);

            /**
             * Figure out why the minecart is travel onto a empty tile when there is a ending?
             */

            controller.lastPos = controller.nextPos;
            controller.nextPos = nextPosition;
            controller.currentTime = 0.0f;
            controller.currentDir = nextDirection;
        }
    }
}