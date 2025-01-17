#pragma once

#include <Maize.h>

#include "Rail.h"

// TODO: Separate this component
struct PlaceGridTile
{
    Maize::Vec2i chunk;
    Maize::Vec2i local;

    Maize::IntRect atlas;
    Maize::Vec2i gridOffset;

    Rail::Type railType;

    PlaceGridTile() = default;

    PlaceGridTile(Maize::Vec2i chunk, Maize::Vec2i local, const Maize::IntRect& atlas, Maize::Vec2i gridOffset, Rail::Type railType)
        : chunk(chunk), local(local), atlas(atlas), gridOffset(gridOffset), railType(railType) {}
};