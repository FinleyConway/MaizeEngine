#pragma once

#include <Maize.h>

struct RailPathRequest
{
    Maize::Vec2i startPosition;
    Maize::Vec2i endPosition;

    RailPathRequest() = default;

    RailPathRequest(Maize::Vec2i startPosition, Maize::Vec2i endPosition) :
        startPosition(startPosition), endPosition(endPosition)
    {
    }
};