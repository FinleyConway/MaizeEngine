#pragma once

#include <Maize.h>

#include "Components/Grid.h"
#include "Components/PlaceChunkTile.h"
#include "Utils/RailTile.h"

struct ChunkManager;
struct PlaceRailData;
struct RailSelector;
struct RailTile;

class MineRailPlacement
{
public:
    static void SelectTile(Maize::SystemState s, const Maize::Position& p, const RailSelector& selector);

    static void PlaceTile(Maize::SystemState s, Maize::Entity e, Maize::GridRenderer& gridRenderer,
                          Grid<RailTile>& grid, const PlaceChunkTile<PlaceRailData>& placeTile);

private:
    static void CreateChunk(Maize::SystemState s, Maize::Entity entity, ChunkManager* chunkManager,
        const RailSelector& selector, Maize::Vec2i chunkPosition, Maize::Vec2i chunkSize, Maize::Vec2i cellSize);
};
