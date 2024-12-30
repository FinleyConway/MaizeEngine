#pragma once

#include <Maize.h>

#include "Grid.h"
#include "MineCarMovement.h"
#include "RailController.h"
#include "Rail.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        m_Texture = std::make_shared<sf::Texture>();
        if (!m_Texture->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/asserts/tileset-16x16.png"))
            return;

        CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::Camera());

        auto grid = Grid(10, 10, 32);
        grid.Set(0, 0, { Rail::Type::NorthRight }); // naming is correct in terms of gates but confusing when thinking about it
        grid.Set(0, 1, { Rail::Type::Vertical });
        grid.Set(0, 2, { Rail::Type::Vertical });
        grid.Set(0, 3, { Rail::Type::SouthRight });
        grid.Set(1, 3, { Rail::Type::Horizontal });
        grid.Set(2, 3, { Rail::Type::Horizontal });
        grid.Set(3, 3, { Rail::Type::SouthLeft });
        grid.Set(3, 2, { Rail::Type::Vertical });
        grid.Set(3, 1, { Rail::Type::Vertical });
        grid.Set(3, 0, { Rail::Type::NorthLeft });
        grid.Set(2, 0, { Rail::Type::Horizontal });
        grid.Set(1, 0, { Rail::Type::Horizontal });

        std::array<sf::Vertex, 6> vertices;
        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, 32);
        vertices[2].position = sf::Vector2f(32, 0);
        vertices[3].position = sf::Vector2f(0, 32);
        vertices[4].position = sf::Vector2f(32, 32);
        vertices[5].position = sf::Vector2f(32, 0);

        Maize::Mesh mesh;
        mesh.AddVertices(vertices);

        auto gridE = CreateEntity(Maize::Vec2f(0, 0), true, false, grid);

        CreateEntity(grid.CartesianToPixel(0, 1), false, false,
            Maize::MeshRenderer(mesh),
            RailController(grid.CartesianToPixel(0, 1), gridE)
        );

        AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
    }

    virtual void OnEnd() override {}

private:
    std::shared_ptr<sf::Texture> m_Texture;

    // Vertical   = { 16, 00, 16, 16 }
    // Horizontal = { 64, 32, 16, 16 }

    // NorthRight = { 128, 00, 16, 16 }
    // NorthLeft  = { 144, 00, 16, 16 }
    // SouthRight = { 128, 16, 16, 16 }
    // SouthLeft  = { 144, 16, 16, 16 }
};
