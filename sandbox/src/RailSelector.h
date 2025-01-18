#pragma once

#include <Maize.h>

#include "Rail.h"

// TODO: Separate this component
struct RailSelector
{
    enum class AxisLock
    {
        None, X, Y, XY, YX
    };

    Rail::Type currentType = Rail::Type::None;
    AxisLock lock = AxisLock::None;
    bool isLocked = false;
    Maize::Vec2f initMouse;

    std::unordered_map<Rail::Type, Maize::IntRect> railType;

    std::weak_ptr<sf::Texture> texture;
    Maize::Vec2i gridOffset = Maize::Vec2i(0, 64);

    RailSelector() = default;

    RailSelector(const std::shared_ptr<sf::Texture>& texture, const std::unordered_map<Rail::Type, Maize::IntRect>& railTypes)
        : railType(railTypes), texture(texture) {}

    Maize::IntRect GetAtlas(Rail::Type type) const
    {
        if (railType.contains(type))
        {
            return railType.at(type);
        }

        return Maize::IntRect();
    }
};
