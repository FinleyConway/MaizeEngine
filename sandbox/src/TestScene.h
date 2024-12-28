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

        std::vector<uint8_t> data1;
        data1.assign(32*32*4, 128);
        textureRed = std::make_shared<sf::Texture>(sf::Vector2u(32, 32));
        textureRed->update(data1.data());

        const auto sprite = Maize::Sprite(texture, { 0, 0, 32, 32 });
        const auto spriteRed = Maize::Sprite(textureRed, { 0, 0, 32, 32 });

        CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::Camera());

        auto grid = Grid(10, 10, 32);
        grid.Set(0, 3, { RailType::NorthRight }); grid.Set(1, 3, { RailType::Horizontal }); grid.Set(2, 3, { RailType::NorthRight });
        grid.Set(0, 2, { RailType::Vertical });                                                                grid.Set(2, 2, { RailType::Vertical });
        grid.Set(0, 1, { RailType::Vertical });                                                                grid.Set(2, 1, { RailType::Vertical });
        grid.Set(0, 0, { RailType::SouthLeft }); grid.Set(1, 0, { RailType::Horizontal });  grid.Set(2, 0, { RailType::SouthLeft });

        CreateEntity(grid.CartesianToPixel(0, 0), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(0, 1), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(0, 2), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(0, 3), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(1, 3), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(1, 0), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(2, 3), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(2, 2), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(2, 1), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(grid.CartesianToPixel(2, 0), true, false, Maize::SpriteRenderer(spriteRed));


        auto gridE = CreateEntity(Maize::Vec2f(0, 0), true, false, grid);

        CreateEntity(grid.CartesianToPixel(0, 1), false, false,
            Maize::SpriteRenderer(sprite),
            RailController(grid.CartesianToPixel(0, 1), gridE)
        );

        AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
    }

    virtual void OnEnd() override {}

private:
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Texture> textureRed;
};
