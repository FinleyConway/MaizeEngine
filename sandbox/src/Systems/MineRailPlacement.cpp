#include "MineRailPlacement.h"

#include "Components/ChunkManager.h"
#include "Components/RailSelector.h"
#include "Components/PlaceChunkTile.h"
#include "Utils/GridConversion.h"
#include "Utils/PlaceRailData.h"

void MineRailPlacement::SelectTile(Maize::SystemState s, const Maize::Position& p, const RailSelector& selector)
{
    auto* input = s.GetSingleton<Maize::Input>();
    auto* chunkManager = s.GetSingleton<ChunkManager>();

    GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

    const auto chunkSize = chunkManager->chunkSize;
    const auto cellSize = chunkManager->cellSize;
    const auto gridPosition = GridConversion::PixelToGrid(p, cellSize);
    const auto chunkPosition = GridConversion::GridToChunk(gridPosition, chunkSize);
    const auto localPosition = GridConversion::GridToChunkLocal(gridPosition, chunkSize);
    auto entity = chunkManager->TryGetChunk(chunkPosition);

    if (input->GetMouseButtonHeld(Maize::MouseCode::Left))
    {
        CreateChunk(s, entity, chunkManager, selector, chunkPosition, chunkSize, cellSize);

        const auto data = PlaceRailData(
            selector.GetBitRail(Rail::ToBitset(selector.currentType)),
            selector.gridOffset,
            selector.currentType
        );

        entity.AddComponent(PlaceChunkTile(chunkPosition, localPosition, data));
    }
    else if (input->GetMouseButtonHeld(Maize::MouseCode::Right))
    {
        if (!entity.IsNull())
        {
            const auto data = PlaceRailData(
                selector.GetBitRail(Rail::ToBitset(Rail::Type::None)),
                selector.gridOffset,
                Rail::Type::None
            );

            entity.AddComponent(PlaceChunkTile(chunkPosition, localPosition, data));
        }
    }
}

void MineRailPlacement::PlaceTile(Maize::SystemState s, Maize::Entity e, Maize::GridRenderer& gridRenderer,
    Grid<RailTile>& grid, const PlaceChunkTile<PlaceRailData>& placeTile)
{
    const auto* chunkManager = s.GetSingleton<ChunkManager>();

    GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

    const auto& data = placeTile.data;
    const auto chunkSize = chunkManager->chunkSize;
    const auto cellSize = chunkManager->cellSize;

    grid.Set(placeTile.local, chunkSize, { data.railType });
    gridRenderer.mesh.Set(placeTile.local, cellSize, chunkSize, data.atlas, data.gridOffset);

    e.RemoveComponent<PlaceChunkTile<PlaceRailData>>();
}

void MineRailPlacement::CreateChunk(Maize::SystemState s, Maize::Entity entity, ChunkManager* chunkManager,
    const RailSelector& selector, Maize::Vec2i chunkPosition, Maize::Vec2i chunkSize, Maize::Vec2i cellSize)
{
    if (entity.IsNull())
    {
        const auto chunkGridPosition = GridConversion::ChunkToGrid(chunkPosition, chunkSize);
        const auto pixelPosition = GridConversion::GridToPixel(chunkGridPosition, cellSize);

        entity = s.CreateEntity(pixelPosition,
            Maize::GridRenderer(Maize::MeshGrid(chunkSize, cellSize), selector.texture),
            Grid<RailTile>(chunkSize)
        );

        chunkManager->chunks.emplace(chunkPosition, entity);
    }
}
