#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

Maize::FloatRect GetMeshBounds(const std::vector<sf::Vertex>& mesh)
{
    auto minX = std::numeric_limits<float>::max();
    auto minY = std::numeric_limits<float>::max();
    auto maxX = std::numeric_limits<float>::min();
    auto maxY = std::numeric_limits<float>::min();

    for (const auto& vertex : mesh)
    {
        minX = std::min(minX, vertex.position.x);
        minY = std::min(minY, vertex.position.y);
        maxX = std::max(maxX, vertex.position.x);
        maxY = std::max(maxY, vertex.position.y);
    }

    return Maize::FloatRect(minX, minY, maxX, maxY);
}

TEST_CASE("Mesh Class Tests", "[Mesh]")
{
   Maize::Mesh mesh;

    SECTION("Adding vertices updates the vertex count and bounds")
    {
        std::vector vertices =
        {
            sf::Vertex(sf::Vector2f(1.0f, 1.0f)),
            sf::Vertex(sf::Vector2f(2.0f, 3.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 2.0f))
        };

        mesh.AddVertices(vertices);

        REQUIRE(mesh.GetVertexCount() == vertices.size());
        REQUIRE(mesh.GetBounds() == GetMeshBounds(vertices));
    }

    SECTION("Adding vertices with predefined bounds")
    {
        std::vector vertices =
        {
            sf::Vertex(sf::Vector2f(1.0f, 1.0f)),
            sf::Vertex(sf::Vector2f(2.0f, 3.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 2.0f))
        };
        auto predefinedBounds = Maize::FloatRect(0.0f, 0.0f, 3.0f, 3.0f);

        mesh.AddVertices(vertices, predefinedBounds);

        REQUIRE(mesh.GetVertexCount() == vertices.size());
        REQUIRE(mesh.GetBounds() == predefinedBounds);
    }

    SECTION("Clearing the mesh")
    {
        std::vector vertices =
        {
            sf::Vertex(sf::Vector2f(1.0f, 1.0f)),
            sf::Vertex(sf::Vector2f(2.0f, 3.0f))
        };

        mesh.AddVertices(vertices);
        REQUIRE(mesh.GetVertexCount() == vertices.size());

        mesh.Clear();
        REQUIRE(mesh.GetVertexCount() == 0);
        REQUIRE(mesh.GetBounds() == Maize::FloatRect());
    }

    SECTION("Mesh bounds calculation")
    {
        std::vector vertices =
        {
            sf::Vertex(sf::Vector2f(1.0f, 1.0f)),
            sf::Vertex(sf::Vector2f(3.0f, 3.0f)),
            sf::Vertex(sf::Vector2f(-1.0f, -1.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 2.0f))
        };

        mesh.AddVertices(vertices);
        auto expectedBounds = Maize::FloatRect(-1.0f, -1.0f, 3.0f, 3.0f);

        REQUIRE(GetMeshBounds(vertices) == expectedBounds);
    }
}
