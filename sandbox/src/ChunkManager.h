#pragma once

#include <Maize.h>

#include "GridConversion.h"

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

    Maize::Entity TryGetChunk(Maize::Vec2i chunkPosition) const
    {
        if (chunks.contains(chunkPosition)) return chunks.at(chunkPosition);
        return Maize::Entity();
    }
};

