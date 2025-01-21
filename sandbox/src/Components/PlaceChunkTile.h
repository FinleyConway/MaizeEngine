#pragma once

#include <Maize.h>

template<typename T>
struct PlaceChunkTile
{
    Maize::Vec2i chunk;
    Maize::Vec2i local;

    T data;

    PlaceChunkTile() = default;

    PlaceChunkTile(Maize::Vec2i chunk, Maize::Vec2i local, const T& data)
        : chunk(chunk), local(local), data(data) {}
};