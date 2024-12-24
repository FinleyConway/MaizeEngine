#include "PrecompiledHeader.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize
{
    SpatialHashGrid::SpatialHashGrid(uint16_t cellSize): m_CellSize(cellSize)
    {
        CORE_ASSERT(cellSize != 0, "Spatial hash grid cell size must be larger then 0!")
    }

    void SpatialHashGrid::Insert(flecs::entity_t e, const FloatRect& size)
    {
        // convert entity bounds to grid bounds
        const auto top = Vec2f(size.x, size.y);
        const auto bottom = Vec2f(size.x + size.width, size.y + size.height);

        // convert bounds into grid positions
        const auto topLeft = PixelToGrid(top);
        const auto bottomRight = PixelToGrid(bottom);

        // loop through region and check if it's within the grid
        for (int32_t x = topLeft.x; x <= bottomRight.x; x++)
        {
            for (int32_t y = topLeft.y; y <= bottomRight.y; y++)
            {
                m_Grid[Vec2i(x, y)].emplace_back(e);
                m_EntityPositions[e].emplace_back(Vec2i(x, y));
            }
        }
    }

    void SpatialHashGrid::Remove(flecs::entity_t e)
    {
        if (!m_EntityPositions.contains(e)) return;

        for (auto index : m_EntityPositions.at(e))
        {
            if (m_Grid.contains(index))
            {
                // loop through the cells contents and find and erase
                auto& cell = m_Grid.at(index);
                const auto it = std::ranges::find(cell, e);

                if (it != cell.end())
                {
                    cell.erase(it);
                }

                if (cell.empty())
                {
                    m_Grid.erase(index);
                }
            }
        }

        m_EntityPositions.erase(e);
    }

    void SpatialHashGrid::Relocate(flecs::entity_t e, const FloatRect& size)
    {
        // remove entity from the grid
        Remove(e);

        // relocate entity into a new cell based on size
        Insert(e, size);
    }

    std::vector<flecs::entity_t> SpatialHashGrid::Query(const FloatRect& region)
    {
        // convert entity bounds to grid bounds
        const auto top = Vec2f(region.x, region.y);
        const auto bottom = Vec2f(region.x + region.width, region.y + region.height);

        // convert bounds into grid positions
        const auto topLeft = PixelToGrid(top);
        const auto bottomRight = PixelToGrid(bottom);

        std::vector<flecs::entity_t> entities;
        std::unordered_set<flecs::entity_t> uniqueEntities;

        // loop through region and check if it's within the grid
        for (int32_t x = topLeft.x; x <= bottomRight.x; x++)
        {
            for (int32_t y = topLeft.y; y <= bottomRight.y; y++)
            {
                // if it is
                if (m_Grid.contains(Vec2i(x, y)))
                {
                    // get all entities in that cell
                    for (auto& entity : m_Grid.at(Vec2i(x, y)))
                    {
                        // check if the entity is unique (to avoid copies)
                        if (uniqueEntities.insert(entity).second) // <- returns if it was successfully inserted
                        {
                            entities.emplace_back(entity); // copy to query
                        }
                    }
                }
            }
        }

        return entities;
    }

    void SpatialHashGrid::SetCellSize(uint16_t cellSize)
    {
        CORE_ASSERT(cellSize != 0, "Spatial hash grid cell size must be larger then 0!")

        m_CellSize = cellSize;
    }

    Vec2i SpatialHashGrid::PixelToGrid(Vec2f pixel) const
    {
        const int32_t gridX = std::floor(pixel.x / m_CellSize);
        const int32_t gridY = std::floor(pixel.y / m_CellSize);

        return Vec2i(gridX, gridY);
    }
} // Maize