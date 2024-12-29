#pragma once

#include <Maize.h>

#include "Grid.h"
#include "MineCarMovement.h"
#include "RailController.h"
#include "RailTypes.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        std::vector<uint8_t> data;
        data.assign(32*32*4, 255);
        texture = std::make_shared<sf::Texture>(sf::Vector2u(32, 32));
        texture->update(data.data());

        CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::Camera());

        auto grid = Grid(10, 10, 32);

        std::array<sf::Vertex, 6> vertices;
        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, 32);
        vertices[2].position = sf::Vector2f(32, 0);
        vertices[3].position = sf::Vector2f(0, 32);
        vertices[4].position = sf::Vector2f(32, 32);
        vertices[5].position = sf::Vector2f(32, 0);

        Maize::Mesh mesh;
        mesh.AddVertices(vertices);

        CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::MeshRenderer(mesh));

        //auto mineCarEntity = CreateEntity(Maize::Vec2f(0, 0), true, false, grid);

        /*CreateEntity(grid.CartesianToPixel(0, 1), false, false,
            RailController(grid.CartesianToPixel(0, 1), gridE)
        );

        AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);*/
    }

    virtual void OnEnd() override {}

private:
    std::shared_ptr<sf::Texture> texture;

    // Vertical   = { 16, 00, 16, 16 }
    // Horizontal = { 64, 32, 16, 16 }

    // NorthRight = { 128, 00, 16, 16 }
    // NorthLeft  = { 144, 00, 16, 16 }
    // SouthRight = { 128, 16, 16, 16 }
    // SouthLeft  = { 144, 16, 16, 16 }
};
