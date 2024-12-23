#pragma once

#include <unordered_map>
#include <vector>

#include <flecs.h>

#include "Maize/Math/Rect.h"
#include "Maize/Math/Vec2.h"

namespace Maize
{
    /**
     * Splits the world into fixed sized chunks allowing to store entities spatially.
     * Good for rendering for when only wanting to render entities near the view.
     */
    class SpatialHashGrid
    {
    public:
        explicit SpatialHashGrid(uint16_t cellSize);

        /**
         * Insert an entity into the hash grid.
         * @param e The entity.
         * @param size The position and size of the entity.
         */
        void Insert(flecs::entity_t e, const FloatRect& size);

        /**
         * Remove an entity from the hash grid.
         * @param e The entity.
         */
        void Remove(flecs::entity_t e);

        /**
         * Move the entity to the new location in the hash grid.
         * @param e The entity.
         * @param size The new position and size of the entity.
         */
        void Relocate(flecs::entity_t e, const FloatRect& size);

        /**
         * Get all entities within a region.
         * @param region The position and size of where you want to search.
         * @return All the entities found.
         */
        std::vector<flecs::entity_t> Query(const FloatRect& region);

        /**
         * Set how big each cell within the grid will be.
         * @param cellSize The size of each cell.
         */
        void SetCellSize(uint16_t cellSize);

    private:
        Vec2i PixelToGrid(Vec2f pixel) const;

    private:
        std::unordered_map<Vec2i, std::vector<flecs::entity_t>> m_Grid;
        std::unordered_map<flecs::entity_t, std::vector<Vec2i>> m_EntityPositions;
        uint16_t m_CellSize = 0;
    };
} // Maize