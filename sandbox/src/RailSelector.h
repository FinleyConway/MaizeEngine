#pragma once

#include <Maize.h>

#include "Rail.h"

struct RailSelector
{
    std::unordered_map<Rail::Type, Maize::FloatRect> railType;
};
