#pragma once

#include <Maize.h>

#include "Rail.h"

struct RailTile
{
    Rail::Type railType = Rail::Type::None;
};

struct Grid
{
    std::vector<RailTile> data;
    int32_t width = 0;
    int32_t height = 0;
    uint16_t cellSize = 32;

    Grid() = default;
    Grid(int32_t width, int32_t height, uint16_t cellSize)
        : width(width), height(height), cellSize(cellSize)
    {
        data.resize(width * height);
    }

    const RailTile& Get(int32_t x, int32_t y) const
    {
        return data[x + y * width];
    }

    RailTile& Get(int32_t x, int32_t y)
    {
        return data[x + y * width];
    }

    bool Set(int32_t x, int32_t y, const RailTile& tile)
    {
        if (IsWithin(x, y))
        {
            data[x + y * width] = tile;

            return true;
        }

        return false;
    }

    bool Has(int32_t x, int32_t y) const
    {
        if (IsWithin(x, y))
        {
            if (data[x + y * width].railType != Rail::Type::None)
            {
                return true;
            }

            return false;
        }

        return false;
    }
    
    bool IsWithin(int32_t x, int32_t y) const
    {
        if (data.empty()) return false;
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    Maize::Vec2f CartesianToPixel(int32_t x, int32_t y) const
    {
        const auto screenX = static_cast<float>(x * cellSize);
        const auto screenY = static_cast<float>(y * cellSize);

        return Maize::Vec2f(screenX, screenY);
    }

    Maize::Vec2i PixelToCartesian(float x, float y) const
    {
        int32_t gridX = 0;
        int32_t gridY = 0;

        if (cellSize != 0) gridX = std::floor(x / cellSize);
        if (cellSize != 0) gridY = std::floor(y / cellSize);

        return Maize::Vec2i(gridX, gridY);
    }
};