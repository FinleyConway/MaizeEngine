#pragma once

#include <Maize.h>

#include "Rail.h"

// TODO: Separate this component
struct RailSelector
{
    Rail::Type currentType = Rail::Type::Vertical; // TODO: change to none
    std::unordered_map<Rail::Type, Maize::IntRect> railType;

    std::weak_ptr<sf::Texture> texture;
    Maize::Vec2i railPivot = Maize::Vec2i(8, 8);
    Maize::Vec2i gridOffset = Maize::Vec2i(-8, -8);

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
