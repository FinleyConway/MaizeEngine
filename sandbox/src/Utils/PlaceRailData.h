#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

struct PlaceRailData
{
    Maize::IntRect atlas;
    Maize::Vec2i gridOffset;
    Rail::Type railType;

    PlaceRailData() = default;

    PlaceRailData(const Maize::IntRect &atlas, Maize::Vec2i gridOffset, Rail::Type railType)
        : atlas(atlas), gridOffset(gridOffset), railType(railType) { }
};