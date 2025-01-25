#pragma once

#include <Maize.h>

class RailTurnDirection;
struct RailRotations;
struct RailController;

class MineCarRotate
{
public:
    static void Rotate(Maize::SystemState s, Maize::Entity e, Maize::SpriteRenderer& spriteRenderer,
        RailController& controller, const RailRotations& rotations);

private:
    static void OnTurnStart(RailController& controller, const RailRotations& rotations);

    static void OnTurn(Maize::SystemState s, Maize::SpriteRenderer& spriteRenderer, RailController& controller);

    static void OnTurnEnd(RailController& controller);

    static const RailTurnDirection* GetTurnDirection(const RailController& controller, const RailRotations& rotations);
};
