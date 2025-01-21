#pragma once

#include <Maize.h>

#include "StaticHelperBase.h"

class GridConversion final : public StaticHelperBase
{
public:
    static Maize::Vec2f GridToPixel(Maize::Vec2i p, Maize::Vec2i cellSize);

    static Maize::Vec2i PixelToGrid(Maize::Vec2f p, Maize::Vec2i cellSize);

    static Maize::Vec2i ChunkToGrid(Maize::Vec2i chunkPosition, Maize::Vec2i chunkSize);

    static Maize::Vec2i GridToChunk(Maize::Vec2i gridPosition, Maize::Vec2i chunkSize);

    static Maize::Vec2i GridToChunkLocal(Maize::Vec2i gridPosition, Maize::Vec2i chunkSize);
};
