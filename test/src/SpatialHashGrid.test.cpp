#include <catch2/catch_test_macros.hpp>

#include "Maize/Utils/SpatialHashGrid.h"

TEST_CASE("Spatial Hash Grid Test", "[SpatialHashGrid]")
{
    flecs::world w;
    auto grid = Maize::SpatialHashGrid(10);

    flecs::entity_t entity1 = w.entity();
    flecs::entity_t entity2 = w.entity();
    flecs::entity_t entity3 = w.entity();

    auto rect1 = Maize::FloatRect(0, 0, 5, 5); // (0, 0)
    auto rect2 = Maize::FloatRect(10, 10, 5, 5); // (1, 1)
    auto rect3 = Maize::FloatRect(20, 20, 5, 5); // (2, 2)

    grid.Insert(entity1, rect1);
    grid.Insert(entity2, rect2);
    grid.Insert(entity3, rect3);

    SECTION("Adding and querying")
    {
        // (0, 0), (1, 0), (0, 1), (1, 1)
        auto queryRegion = Maize::FloatRect(0, 0, 15, 15);
        std::vector<flecs::entity_t> queriedEntities = grid.Query(queryRegion);

        REQUIRE(queriedEntities.size() == 2);
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity1) != queriedEntities.end());
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity2) != queriedEntities.end());
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity3) == queriedEntities.end());
    }

    SECTION("Removing and querying")
    {
        grid.Remove(entity2);

        // (0, 0), (1, 0), (0, 1), (1, 1)
        auto queryRegion = Maize::FloatRect(0, 0, 15, 15);
        std::vector<flecs::entity_t> queriedEntities = grid.Query(queryRegion);

        REQUIRE(queriedEntities.size() == 1);
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity1) != queriedEntities.end());
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity2) == queriedEntities.end());
        REQUIRE(std::find(queriedEntities.begin(), queriedEntities.end(), entity3) == queriedEntities.end());
    }

    SECTION("Relocating")
    {
        grid.Relocate(entity2, rect1);

        auto queryRegion = Maize::FloatRect(0, 0, 0, 0);
        std::vector<flecs::entity_t> queriedEntities = grid.Query(queryRegion);

        REQUIRE(queriedEntities.size() == 2);
    }

    SECTION("Cell collapsing")
    {
        grid.Remove(entity1);
        grid.Remove(entity2);
        grid.Remove(entity3);

        auto queryRegion = Maize::FloatRect(0, 0, 15, 15);
        std::vector<flecs::entity_t> queriedEntities = grid.Query(queryRegion);

        REQUIRE(queriedEntities.empty() == true);
    }
}