#pragma once

#include <Maize.h>

#include "ChunkManager.h"
#include "Grid.h"
#include "MineCarMovement.h"
#include "MineRailPlacement.h"
#include "RailController.h"
#include "RailSelector.h"
#include "Rail.h"

class TestScene final : public Maize::Scene
{
public:
    virtual void OnStart() override
    {
        m_Texture = std::make_shared<sf::Texture>();
        if (!m_Texture->loadFromFile("/home/finley/CLionProjects/MaizeEngine/sandbox/asserts/tileset-16x16.png"))
            return;

        CreateSingleton<ChunkManager>(
            Maize::Vec2<uint16_t>(32, 32),
            Maize::Vec2<uint16_t>(32, 32)
        );

        CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::Camera(2));

        auto sprite = Maize::Sprite(m_Texture, Maize::IntRect(128, 00, 16, 16));

        auto gridE = CreateEntity(Maize::Vec2f(0, 0), true, false,
            RailSelector(GetRailAtlas())
        );

        AddSystem<RailSelector>("Rail Placement", flecs::OnUpdate, MineRailPlacement::Handle);
        //AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, MineCarMovement::Move);
    }

    virtual void OnEnd() override {}

private:
    static std::unordered_map<Rail::Type, Maize::FloatRect> GetRailAtlas()
    {
        std::unordered_map<Rail::Type, Maize::FloatRect> rails;

        rails.emplace(Rail::Type::Vertical,   Maize::FloatRect(016, 00, 16, 16));
        rails.emplace(Rail::Type::Horizontal, Maize::FloatRect(064, 32, 16, 16));
        rails.emplace(Rail::Type::NorthRight, Maize::FloatRect(128, 00, 16, 16));
        rails.emplace(Rail::Type::NorthLeft,  Maize::FloatRect(144, 00, 16, 16));
        rails.emplace(Rail::Type::SouthRight, Maize::FloatRect(128, 16, 16, 16));
        rails.emplace(Rail::Type::SouthLeft,  Maize::FloatRect(144, 16, 16, 16));

        return rails;
    }

private:
    std::shared_ptr<sf::Texture> m_Texture;
};
