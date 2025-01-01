#pragma once

#include <Maize.h>

template<typename T>
struct Grid
{
public:
    std::vector<T> data;

public:
    Grid() = default;

    Grid(Maize::Vec2i size)
    {
        data.resize(size.x * size.y);
    }

    const T& Get(int32_t x, int32_t y, uint16_t width) const
    {
        return data[x + y * width];
    }

    T& Get(int32_t x, int32_t y, uint16_t width)
    {
        return data[x + y * width];
    }

    bool Set(Maize::Vec2i position, Maize::Vec2i size, const T& tile)
    {
        if (IsWithin(position, size))
        {
            data[position.x + position.y * size.x] = tile;

            return true;
        }

        return false;
    }
    
    bool IsWithin(Maize::Vec2i position, Maize::Vec2i size) const
    {
        if (data.empty()) return false;
        return position.x >= 0 && position.y >= 0 && position.x < size.x && position.y < size.y;
    }
};