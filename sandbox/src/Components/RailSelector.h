#pragma once

#include <Maize.h>

#include "Utils/FuzzyShape.h"
#include "Utils/Rail.h"

// TODO: Separate this component
struct RailSelector
{
    enum class AxisLock { None, X, Y, XY, YX };

    Rail::Type currentType = Rail::Type::None;
    AxisLock lockState = AxisLock::None;
    Maize::Vec2f initialMousePosition;

    std::unordered_map<Rail::TypeBits, Maize::IntRect> autoRails;
    std::vector<FuzzyShape> quadrantShapes;

    // remove these later on
    std::weak_ptr<sf::Texture> texture;
    Maize::Vec2i gridOffset = Maize::Vec2i(0, 32);

    RailSelector() = default;

    RailSelector(const std::shared_ptr<sf::Texture>& texture, const std::unordered_map<Rail::TypeBits, Maize::IntRect>& autoRails,
        const std::vector<FuzzyShape>& quadrantShapes)
        : autoRails(autoRails), quadrantShapes(quadrantShapes), texture(texture) {}

    Maize::IntRect GetBitRail(uint8_t type) const
    {
        if (autoRails.contains(type))
        {
            return autoRails.at(type);
        }

        return Maize::IntRect();
    }
};
