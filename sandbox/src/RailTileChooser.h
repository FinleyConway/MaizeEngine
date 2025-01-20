#pragma once

#include <Maize.h>

#include "RailSelector.h"
#include "ChunkManager.h"
#include "Grid.h"
#include "GridConversion.h"
#include "RailTile.h"
#include "Rail.h"

class RailTileChooser
{
public:
    static void ChooseRailType(Maize::SystemState s, Maize::Entity e, Maize::Position& position, Maize::SpriteRenderer& spriteRenderer, RailSelector& selector)
    {
        auto* input = s.GetSingleton<Maize::Input>();
        const auto* chunkManager = s.GetSingleton<ChunkManager>();

        GAME_ASSERT(chunkManager != nullptr, "ChunkManager is nullptr");

        const auto cellSize = chunkManager->cellSize;
        const auto mousePosition = input->mousePosition;
        const auto gridPosition = GridConversion::PixelToGrid(mousePosition, cellSize);
        const auto tilePosition = GridConversion::GridToPixel(gridPosition, cellSize);

        if (!input->GetMouseButtonHeld(Maize::MouseCode::Left))
        {
            // TODO: decide what the tile type is based on the surrounding tiles
            GAME_LOG_INFO((int)EvaluateSurroundingTiles(chunkManager, gridPosition));
            const auto tile = GetTypeFromPointInSquare(selector.currentType, mousePosition, tilePosition, cellSize);

            selector.lockState = GetAxisLock(tile);
            selector.currentType = tile;
            selector.initialMousePosition = tilePosition;

            spriteRenderer.sprite.SetTextureRect(selector.GetAtlas(tile));
            position = tilePosition;
        }
        else
        {
            LockPositionAxis(position, selector, tilePosition);
        }
    }

private:
    static uint8_t EvaluateSurroundingTiles(const ChunkManager* chunkManager, Maize::Vec2i gridPosition)
    {
        uint8_t bitset = 0;

        static std::array surroundingTiles =
        {
            Maize::Vec2i(+0, +1), // north
            Maize::Vec2i(+1, +1), // north-east
            Maize::Vec2i(+1, +0), // east
            Maize::Vec2i(+1, -1), // south-east
            Maize::Vec2i(+0, -1), // south
            Maize::Vec2i(-1, -1), // south-west
            Maize::Vec2i(-1, +0), // west
            Maize::Vec2i(-1, +1), // north-west
        };

        // go through each direction
        for (uint8_t i = 0; i < 8; i++)
        {
            const auto direction = surroundingTiles[i];
            const auto tilePosition = gridPosition + direction;
            const auto chunkPosition = GridConversion::GridToChunk(tilePosition, chunkManager->chunkSize);
            const auto localPosition = GridConversion::GridToChunkLocal(tilePosition, chunkManager->chunkSize);

            const auto entity = chunkManager->TryGetChunk(chunkPosition);

            if (entity.IsNull()) continue;

            if (const auto* grid = entity.TryGetComponent<Grid<RailTile>>())
            {
                const uint8_t bitDirection = 1 << i;

                GAME_ASSERT(Rail::IsValidDirection(bitDirection), "Invalid direction!");

                const auto tileDirection = static_cast<Rail::Dir>(bitDirection); // this should be safe
                const auto& tile = grid->Get(localPosition, chunkManager->chunkSize);

                // if current type and offset type can connect
                if (Rail::GetNextTravellingDir(tileDirection, tile.railType) == tileDirection)
                {
                    // update bitset direction
                    bitset |= 1 << i;
                }
            }
        }

        return bitset;
    }

    static Rail::Type GetRailTypeQuadRant(Rail::Type currentType, int32_t x, int32_t y)
    {
        if (x == 0)
        {
            if (y == 0) return Rail::Type::Diagonal;              // top-left
            if (y == 1) return Rail::Type::Horizontal;            // middle-left

            return Rail::Type::ADiagonal;                         // bottom-left
        }

        if (x == 1)
        {
            if (y == 0 || y == 2) return Rail::Type::Vertical;    // top-middle, bottom-middle

            return currentType;                                   // center-middle
        }

        if (y == 0) return Rail::Type::ADiagonal;                 // top-right
        if (y == 1) return Rail::Type::Horizontal;                // middle-right

        return Rail::Type::Diagonal;                              // bottom-right
    }

    static Rail::Type GetTypeFromPointInSquare(Rail::Type currentType, Maize::Vec2f mousePosition, Maize::Vec2f tilePosition, Maize::Vec2i squareSize)
    {
        constexpr uint8_t quadrants = 3;  // number of sections per axis (for a 3x3 grid)
        const auto quadrantSize = Maize::Vec2f(squareSize / quadrants);

        // get the quadrant indices based on mouse position
        const auto relMouse = mousePosition - tilePosition;
        const auto point = Maize::Vec2i(relMouse.x / quadrantSize.x, relMouse.y / quadrantSize.y);

        return GetRailTypeQuadRant(currentType, point.x, point.y);
    }

    static RailSelector::AxisLock GetAxisLock(Rail::Type currentType)
    {
        switch (currentType)
        {
            case Rail::Type::Vertical:   return RailSelector::AxisLock::Y;
            case Rail::Type::Horizontal: return RailSelector::AxisLock::X;
            case Rail::Type::Diagonal:   return RailSelector::AxisLock::XY;
            case Rail::Type::ADiagonal:  return RailSelector::AxisLock::YX;
            default:                     return RailSelector::AxisLock::None;
        }
    }

    static void LockPositionAxis(Maize::Position& position, const RailSelector& selector, Maize::Vec2f tilePosition)
    {
        // lock the x-axis
        if (selector.lockState == RailSelector::AxisLock::X)
        {
            position.x = tilePosition.x;
        }
        // lock the y-axis
        else if (selector.lockState == RailSelector::AxisLock::Y)
        {
            position.y = tilePosition.y;
        }
        // lock the diagonal axis
        else if (selector.lockState == RailSelector::AxisLock::XY)
        {
            const auto delta = tilePosition - selector.initialMousePosition;
            const auto locked = selector.initialMousePosition + Maize::Vec2f(delta.x, delta.x);

            position.x = locked.x;
            position.y = locked.y;
        }
        // lock the anti-diagonal axis
        else if (selector.lockState == RailSelector::AxisLock::YX)
        {
            const auto delta = tilePosition - selector.initialMousePosition;
            const auto locked = selector.initialMousePosition + Maize::Vec2f(delta.x, -delta.x);

            position.x = locked.x;
            position.y = locked.y;
        }
    }
};
