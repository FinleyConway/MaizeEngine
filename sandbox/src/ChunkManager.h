#pragma once

#include <Maize.h>

struct ChunkManager
{
public:
    std::unordered_map<Maize::Vec2i, Maize::Entity> chunks;
    Maize::Vec2i chunkSize;
    Maize::Vec2i cellSize;

public:
    ChunkManager() = default;
    ChunkManager(Maize::Vec2<uint16_t> chunkSize, Maize::Vec2<uint16_t> cellSize)
        : chunkSize(chunkSize), cellSize(cellSize) {}

    Maize::FloatRect GetChunkBounds() const
    {
        return Maize::FloatRect(0 , 0, cellSize.x * chunkSize.x, cellSize.y * chunkSize.y);
    }

    Maize::Entity TryGetChunk(Maize::Vec2i chunkPosition) const
    {
        if (chunks.contains(chunkPosition)) return chunks.at(chunkPosition);
        return Maize::Entity();
    }
};

