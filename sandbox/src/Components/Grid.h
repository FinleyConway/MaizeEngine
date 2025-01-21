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

    const T& Get(Maize::Vec2i position, Maize::Vec2i size) const
    {
        return data[position.x + position.y * size.x];
    }

    T& Get(Maize::Vec2i position, Maize::Vec2i size)
    {
        return data[position.x + position.y * size.x];
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