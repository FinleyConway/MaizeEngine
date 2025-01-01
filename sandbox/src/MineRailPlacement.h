#pragma once

#include <Maize.h>

#include "ChunkManager.h"
#include "RailSelector.h"
#include "Grid.h"
#include "RailTile.h"

class MineRailPlacement
{
public:
    static void Handle(Maize::SystemState s, Maize::Entity e, RailSelector& selector)
    {
        auto* input = s.GetSingleton<Maize::Input>();
        auto* chunkManager = s.GetSingleton<ChunkManager>();

        GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

        if (input->GetMouseButtonDown(Maize::MouseCode::Left))
        {
            const auto mousePosition = input->mousePosition;
            const auto gridPosition = GridConversion::PixelToCartesian(mousePosition, chunkManager->chunkSize);

            if (auto* grid = chunkManager->TryGetChunkComponent<Grid<RailTile>>(gridPosition))
            {
                GAME_LOG_INFO("Found grid");
            }
            else
            {
                GAME_LOG_INFO("Failed to find grid");
                Create(s, chunkManager, gridPosition);
            }
        }
    }

private:
    static void Create(Maize::SystemState s, ChunkManager* chunkManager, Maize::Vec2i gridPosition)
    {
        const auto chunkPosition = GridConversion::CartesianToChunk(gridPosition, chunkManager->chunkSize);
        const auto pixelPosition = GridConversion::CartesianToPixel(gridPosition, chunkManager->chunkSize);

        const auto entity = s.CreateEntity(pixelPosition, true, false,
            Grid<RailTile>(chunkManager->chunkSize)
        );

        chunkManager->chunks[chunkPosition] = entity;
    }
};
