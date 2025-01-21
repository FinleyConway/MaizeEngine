#include "GridConversion.h"

Maize::Vec2f GridConversion::GridToPixel(Maize::Vec2i p, Maize::Vec2i cellSize)
{
    const auto screenX = static_cast<float>(p.x * cellSize.x);
    const auto screenY = static_cast<float>(p.y * cellSize.y);

    return Maize::Vec2f(screenX, screenY);
}

Maize::Vec2i GridConversion::PixelToGrid(Maize::Vec2f p, Maize::Vec2i cellSize)
{
    int32_t gridX = 0;
    int32_t gridY = 0;

    if (cellSize.x != 0) gridX = std::floor(p.x / cellSize.x);
    if (cellSize.y != 0) gridY = std::floor(p.y / cellSize.y);

    return Maize::Vec2i(gridX, gridY);
}

Maize::Vec2i GridConversion::ChunkToGrid(Maize::Vec2i chunkPosition, Maize::Vec2i chunkSize)
{
    const int32_t chunkX = chunkPosition.x * chunkSize.x;
    const int32_t chunkY = chunkPosition.y * chunkSize.y;

    return Maize::Vec2i(chunkX, chunkY);
}

Maize::Vec2i GridConversion::GridToChunk(Maize::Vec2i gridPosition, Maize::Vec2i chunkSize)
{
    int32_t chunkX = 0;
    int32_t chunkY = 0;

    if (chunkSize.x != 0) chunkX = gridPosition.x >= 0 ? gridPosition.x / chunkSize.x : (gridPosition.x - chunkSize.x + 1) / chunkSize.x;
    if (chunkSize.y != 0) chunkY = gridPosition.y >= 0 ? gridPosition.y / chunkSize.y : (gridPosition.y - chunkSize.y + 1) / chunkSize.y;

    return Maize::Vec2i(chunkX, chunkY);
}

Maize::Vec2i GridConversion::GridToChunkLocal(Maize::Vec2i gridPosition, Maize::Vec2i chunkSize)
{
    int32_t localX = 0;
    int32_t localY = 0;

    if (chunkSize.x != 0) localX = gridPosition.x % chunkSize.x;
    if (chunkSize.y != 0) localY = gridPosition.y % chunkSize.y;

    if (localX < 0) localX += chunkSize.x;
    if (localY < 0) localY += chunkSize.y;

    return Maize::Vec2i(localX, localY);
}
