#pragma once

#include <unordered_map>
#include <vector>

#include <flecs.h>

#include "Maize/Math/Rect.h"
#include "Maize/Math/Vec2.h"

namespace Maize
{
    class SpatialHashGrid
    {
    public:
        explicit SpatialHashGrid(uint16_t cellSize);

        void Insert(flecs::entity_t e, const FloatRect& size);

        void Remove(flecs::entity_t e);

        void Relocate(flecs::entity_t e, const FloatRect& size);

        std::vector<flecs::entity_t> Query(const FloatRect& region);

        void SetCellSize(uint16_t cellSize);

    private:
        Vec2i PixelToGrid(Vec2f pixel) const;

    private:
        std::unordered_map<Vec2i, std::vector<flecs::entity_t>> m_Grid;
        std::unordered_map<flecs::entity_t, std::vector<Vec2i>> m_EntityPositions;
        uint16_t m_CellSize = 0;
    };
} // Maize