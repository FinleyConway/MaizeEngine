#pragma once

#include <Maize.h>

#include "Components/RailSelector.h"
#include "Utils/Rail.h"

class FuzzyShape;
struct ChunkManager;
struct RailSelector;

class RailTileChooser
{
public:
    static void ChooseRailType(Maize::SystemState s, Maize::Position& position, Maize::SpriteRenderer& spriteRenderer, RailSelector& selector);

private:
    static Rail::Type GetTileType(const ChunkManager* chunkManager, Maize::Vec2i gridPosition);

    static uint8_t EvaluateSurroundingTiles(const ChunkManager* chunkManager, Maize::Vec2i gridPosition);

    static const FuzzyShape* GetBestMatchedShape(uint8_t bitset, const RailSelector& selector);

    static Rail::Type GetTypeFromPointInSquare(const FuzzyShape& shape, Maize::Vec2f mousePosition, Maize::Vec2f tilePosition, Maize::Vec2i squareSize);

    static RailSelector::AxisLock GetAxisLock(Rail::Type currentType);

    static void LockPositionAxis(Maize::Position& position, const RailSelector& selector, Maize::Vec2f tilePosition);
};
