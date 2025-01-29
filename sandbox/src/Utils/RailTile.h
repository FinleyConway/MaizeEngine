#pragma once

#include "Utils/Rail.h"

struct RailTile
{
    Rail::Type railType = Rail::Type::None;

    int32_t gCost = 0;
    int32_t hCost = 0;
    int32_t fCost = gCost + hCost;
    Maize::Vec2i cameFromNode;
};
