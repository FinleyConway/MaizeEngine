#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

struct PlaceRailData
{
    Maize::IntRect atlas;
    Maize::Vec2i gridOffset;
    Rail::Type railType;
};