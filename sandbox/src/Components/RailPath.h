#pragma once

#include <deque>

#include "Utils/Rail.h"

struct RailPath
{
    std::deque<Rail::Dir> path;

    RailPath() = default;

    RailPath(std::deque<Rail::Dir>&& path) : path(std::move(path)) {}
};
