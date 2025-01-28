#include "RailTileChooser.h"

#include "Components/Grid.h"
#include "Components/ChunkManager.h"
#include "Utils/GridConversion.h"
#include "Utils/FuzzyShape.h"
#include "Utils/RailTile.h"

void RailTileChooser::ChooseRailType(Maize::SystemState s, Maize::Position& position,
    Maize::SpriteRenderer& spriteRenderer, RailSelector& selector)
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
        if (selector.quadrantShapes.empty())
        {
            GAME_LOG_WARN("No quadrant shapes found");
            return;
        }

        const FuzzyShape* currentShape = &selector.quadrantShapes[0];

        if (input->GetButtonHeld(Maize::KeyCode::LShift))
        {
            const auto tileType = GetTileType(chunkManager, gridPosition);
            const Rail::TypeBits tileBits = Rail::ToBitset(tileType);

            if (const auto* bestMatch = GetBestMatchedShape(tileBits, selector))
            {
                currentShape = bestMatch;
            }
        }
        else
        {
            const uint8_t bitset = EvaluateSurroundingTiles(chunkManager, gridPosition);

            if (const auto* bestMatch = GetBestMatchedShape(bitset, selector))
            {
                currentShape = bestMatch;
            }
        }

        if (currentShape != nullptr)
        {
            const auto tile = GetTypeFromPointInSquare(*currentShape, mousePosition, tilePosition, cellSize);

            selector.lockState = GetAxisLock(tile);
            selector.currentType = tile;
            selector.initialMousePosition = tilePosition;

            spriteRenderer.sprite.SetTextureRect(selector.GetBitRail(Rail::ToBitset(tile)));
            position = tilePosition;
        }
    }
    else
    {
        LockPositionAxis(position, selector, tilePosition);
    }
}

Rail::Type RailTileChooser::GetTileType(const ChunkManager* chunkManager, Maize::Vec2i gridPosition)
{
    const auto chunkPosition = GridConversion::GridToChunk(gridPosition, chunkManager->chunkSize);
    auto entity = chunkManager->TryGetChunk(chunkPosition);

    if (auto* grid = entity.TryGetMutComponent<Grid<RailTile>>())
    {
        const auto localPosition = GridConversion::GridToChunkLocal(gridPosition, chunkManager->chunkSize);

        return grid->Get(localPosition, chunkManager->chunkSize).railType;
    }

    return Rail::Type::None;
}

uint8_t RailTileChooser::EvaluateSurroundingTiles(const ChunkManager* chunkManager, Maize::Vec2i gridPosition)
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
        // get the chunk position attempt to get the entity
        const auto direction = surroundingTiles[i];
        const auto tilePosition = gridPosition + direction;
        const auto chunkPosition = GridConversion::GridToChunk(tilePosition, chunkManager->chunkSize);
        const auto localPosition = GridConversion::GridToChunkLocal(tilePosition, chunkManager->chunkSize);
        const auto entity = chunkManager->TryGetChunk(chunkPosition);

        if (const auto* grid = entity.TryGetComponent<Grid<RailTile>>())
        {
            // get the current direction and nearby tile type
            const auto currentDirection = static_cast<Rail::Dir>(1 << i);
            const auto& tile = grid->Get(localPosition, chunkManager->chunkSize);

            // check if current direction can travel to rail type
            if (Rail::CanDirToType(currentDirection, tile.railType)) bitset |= 1 << i;
        }
    }

    return bitset;
}

const FuzzyShape* RailTileChooser::GetBestMatchedShape(uint8_t bitset, const RailSelector& selector)
{
    // search unless the override button is pressed
    for (const auto& shape : selector.quadrantShapes)
    {
        if (shape.Match(bitset))
        {
            return &shape; // this *should* be safe
        }
    }

    return nullptr;
}

Rail::Type RailTileChooser::GetTypeFromPointInSquare(const FuzzyShape& shape, Maize::Vec2f mousePosition,
                                                     Maize::Vec2f tilePosition, Maize::Vec2i squareSize)
{
    constexpr uint8_t quadrants = 3;  // number of sections per axis (for a 3x3 grid)
    const auto quadrantSize = Maize::Vec2f(squareSize / quadrants);

    // get the quadrant indices based on mouse position
    const auto relMouse = mousePosition - tilePosition;
    const auto point = Maize::Vec2i(relMouse.x / quadrantSize.x, relMouse.y / quadrantSize.y);

    return shape.GetType(point.x, point.y);
}

RailSelector::AxisLock RailTileChooser::GetAxisLock(Rail::Type currentType)
{
    switch (currentType)
    {
        case Rail::Type::Vertical:   return RailSelector::AxisLock::Y;
        case Rail::Type::Horizontal: return RailSelector::AxisLock::X;
        default:                     return RailSelector::AxisLock::None;
    }
}

void RailTileChooser::LockPositionAxis(Maize::Position& position, const RailSelector& selector,
    Maize::Vec2f tilePosition)
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
}
