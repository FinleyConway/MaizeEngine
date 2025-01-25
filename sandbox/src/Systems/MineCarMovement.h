#pragma once

#include <Maize.h>

struct ChunkManager;
struct RailController;

class MineCarMovement
{
public:
    static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller);

private:
    static void HandleDirection(const ChunkManager* chunkManager, RailController& controller);
};
