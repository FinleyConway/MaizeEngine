#pragma once

#include <Maize.h>

#include "Components/Grid.h"
#include "Utils/RailTile.h"

struct ChunkManager;
struct RailController;

class MineCarMovement
{
public:
    static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller);

private:
    static void HandleMovement(Maize::SystemState s, Maize::Position& position, RailController& controller, const ChunkManager* chunkManager);

    static void HandleDirection(const ChunkManager* chunkManager, RailController& controller);

    static void HandleNextRail(const Grid<RailTile>* grid, Maize::Vec2i gridPosition, const ChunkManager* chunkManager, RailController& controller);

    static void UpdateRailPosition(Maize::Vec2i gridPosition, Rail::Dir nextDirection, const ChunkManager* chunkManager, RailController& controller);
};
