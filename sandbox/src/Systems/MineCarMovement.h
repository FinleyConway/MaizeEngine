#pragma once

#include <Maize.h>

struct RailRotations;
struct ChunkManager;
struct RailController;

class MineCarMovement
{
public:
    static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller, const RailRotations& rotations);

private:
    static void HandleDirection(const ChunkManager* chunkManager, RailController& controller);

    static void HandleTurning(Maize::Entity e, RailController& controller, const RailRotations& rotations);
};
