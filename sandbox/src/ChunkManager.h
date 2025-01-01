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

    template<typename T>
    T* TryGetChunkComponent(Maize::Vec2i gridPosition)
    {
        return TryGetEntityChunk(gridPosition).TryGetMutComponent<T>();
    }

    Maize::Entity TryGetEntityChunk(Maize::Vec2i gridPosition) const
    {
        const auto chunkPosition = GridConversion::CartesianToChunk(gridPosition, chunkSize);

        if (chunks.contains(chunkPosition)) return chunks.at(chunkPosition);
        return Maize::Entity();
    }
};

