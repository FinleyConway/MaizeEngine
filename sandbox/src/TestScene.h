#pragma once

#include <Maize.h>

/**
 * Direction layout in binary.
 */
namespace RailDir
{
    enum
    {
        None = 0,	// 00000000
        N    = 1,   // 00000001
        NE   = 2,   // 00000010
        E    = 4,   // 00000100
        SE   = 8,   // 00001000
        S    = 16,  // 00010000
        SW   = 32,  // 00100000
        W    = 64,  // 01000000
        NW   = 128  // 10000000
    };
} // RailDir

/**
 * Bitsets that defines the rail type by possible i/o.
 */
namespace RailType
{
    enum
    {
        None  = RailDir::None, // no direction

        StraightNS = RailDir::N | RailDir::S, // vertical rail ↕
        StraightWE = RailDir::W | RailDir::E, // horizontal rail ↔

        LeftSW = RailDir::S | RailDir::W, // South to west turn ↰
        LeftNW = RailDir::N | RailDir::W, // North to west turn ↲

        RightSE = RailDir::S | RailDir::E, // South to east turn ↱
        RightNE = RailDir::N | RailDir::E, // North to east turn ↳

        DiagonalNESW = RailDir::NE | RailDir::SW, // Diagonal left ⤢
        DiagonalNWSE = RailDir::NW | RailDir::SE, // Diagonal right ⤡
    };
} // RailType

struct RailTile
{
    uint8_t direction = RailType::None;
};

struct Grid
{
    std::vector<RailTile> data;
    int32_t width = 0;
    int32_t height = 0;

    Grid() = default;
    Grid(int32_t width, int32_t height) : width(width), height(height)
    {
        data.resize(width * height);
    }

    RailTile& Get(int32_t x, int32_t y)
    {
        return data[x + y * width];
    }

    bool Set(int32_t x, int32_t y, const RailTile& tile)
    {
        if (IsWithin(x, y))
        {
            data[x + y * width] = tile;

            return true;
        }

        return false;
    }

    bool Has(int32_t x, int32_t y) const
    {
        if (IsWithin(x, y))
        {
            if (data[x + y * width].direction != RailDir::None)
            {
                return true;
            }

            return false;
        }

        return false;
    }


    bool IsWithin(int32_t x, int32_t y) const
    {
        if (data.empty()) return false;
        return x >= 0 && y >= 0 && x < width && y < height;
    }
};

struct RailController
{
    float speed = 8.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;

    Maize::Entity grid;

    RailController() = default;
    RailController(Maize::Vec2f lastPos, Maize::Entity grid)
        : lastPos(lastPos), nextPos(lastPos), grid(grid) {}
};

static Maize::Vec2f CartesianToPixel(int32_t x, int32_t y, int32_t cellSizeX, int32_t cellSizeY)
{
    const auto screenX = static_cast<float>(x * cellSizeX);
    const auto screenY = static_cast<float>(y * cellSizeY);

    return Maize::Vec2f(screenX, screenY);
}

static Maize::Vec2i PixelToCartesian(float x, float y, int32_t cellSizeX, int32_t cellSizeY)
{
    int32_t gridX = 0;
    int32_t gridY = 0;

    if (cellSizeX != 0) gridX = std::floor(x / cellSizeX);
    if (cellSizeY != 0) gridY = std::floor(y / cellSizeY);

    return Maize::Vec2i(gridX, gridY);
}

inline void RotateRailClockWise(std::bitset<8>& direction)
{
    // StraightNS   * 2 = DiagonalNESW
    // DiagonalNESW * 2 = StraightWE
    // StraightWE   * 2 = DiagonalNWSE

    const uint64_t dir = direction.to_ulong();

    if (dir & RailType::StraightNS || dir & RailType::DiagonalNESW || dir & RailType::StraightWE)
    {
        // shift the direction to the next direction
        direction = dir * 2;
    }
    else if (direction == RailType::DiagonalNWSE)
    {
        // reset direction
        direction = RailType::StraightNS;
    }
}

static float Lerp(float a, float b, float t) { t = std::clamp(t, 0.0f, 1.0f); return a + (b - a) * t; }

static Maize::Vec2f Lerp(Maize::Vec2f from, Maize::Vec2f to, float time)
{
    const float newX = Lerp(from.x, to.x, time);
    const float newY = Lerp(from.y, to.y, time);

    return Maize::Vec2f(newX, newY);
}

static Maize::Vec2i GetDirectionOffset(uint8_t direction, Maize::Vec2i offset, bool forward)
{
    auto newOffset = offset;

    switch (direction)
    {
        case RailType::StraightNS: // up or down
        {
            if (forward) newOffset.y += 1;
            else newOffset.y -= 1;
            break;
        }
        case RailType::StraightWE: // left or right
        {
            if (forward) newOffset.x += 1;
            else newOffset.x -= 1;
            break;
        }
        case RailType::LeftSW: // up and left
        {
            if (forward) newOffset.x -= 1;
            else newOffset.y -= 1;
            break;
        }
        case RailType::RightSE: // up and right
        {
            if (forward) newOffset.x += 1;
            else newOffset.y -= 1;
            break;
        }
        case RailType::LeftNW: // down and left
        {
            if (forward) newOffset.x -= 1;
            else newOffset.y += 1;
            break;
        }
        case RailType::RightNE: // up and right
        {
            if (forward) newOffset.x += 1;
            else newOffset.y += 1;
            break;
        }
        default:
            GAME_ASSERT(false, "Unknown direction");
            break;
    }

    return newOffset;
}

static void HandleDirection(Grid& grid, Maize::Vec2f& nextPosition, Maize::Vec2f& lastPosition, float& currentTime, bool forward)
{
    const auto gridPos = PixelToCartesian(nextPosition.x, nextPosition.y, 32, 32);
    const auto& tile = grid.Get(gridPos.x, gridPos.y);
    const auto gridPosOffset = GetDirectionOffset(tile.direction, gridPos, forward);
    const auto direction = grid.Get(gridPosOffset.x, gridPosOffset.y).direction;

    if (direction != RailType::None)
    {
        if (forward)
        {
            lastPosition = nextPosition;
            nextPosition = CartesianToPixel(gridPosOffset.x, gridPosOffset.y, 32, 32);
            currentTime = 0.0f;
        }
        else
        {
            nextPosition = lastPosition;
            lastPosition = CartesianToPixel(gridPosOffset.x, gridPosOffset.y, 32, 32);
            currentTime = 1.0f;
        }
    }
}

static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();

    // handle directional input
    float inputValue = 0.0f;
    if (input->GetButtonHeld(Maize::KeyCode::W)) inputValue = 1.0f;
    else if (input->GetButtonHeld(Maize::KeyCode::S)) inputValue = -1.0f;

    if (inputValue != 0.0f)
    {
        if (auto* grid = controller.grid.TryGetMutComponent<Grid>())
        {
            const bool isForward = position.x >= controller.nextPos.x && position.y >= controller.nextPos.y;
            const bool isBackward = position.x <= controller.lastPos.x && position.y <= controller.lastPos.y;

            // going forward
            if (inputValue > 0.0f && isForward)
            {
                HandleDirection(*grid, controller.nextPos, controller.lastPos, controller.currentTime, true);
            }
            else if (inputValue < 0.0f && isBackward)
            {
                HandleDirection(*grid, controller.nextPos, controller.lastPos, controller.currentTime, false);
            }
        }

        controller.currentTime += inputValue * controller.speed * s.DeltaTime();
        controller.currentTime = std::clamp(controller.currentTime, 0.0f, 1.0f);

        const auto lerpPos = Lerp(controller.lastPos, controller.nextPos, controller.currentTime);
        position.x = lerpPos.x;
        position.y = lerpPos.y;
    }
}

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

        auto grid = Grid(10, 10);
        grid.Get(0, 1).direction = RailType::StraightNS;
        grid.Get(0, 2).direction = RailType::StraightNS;
        grid.Get(0, 3).direction = RailType::RightSE;
        grid.Get(1, 3).direction = RailType::StraightWE;
        grid.Get(2, 3).direction = RailType::StraightWE;
        grid.Get(3, 3).direction = RailType::LeftSW;
        grid.Get(3, 2).direction = RailType::StraightNS;
        grid.Get(3, 1).direction = RailType::StraightNS;
        grid.Get(3, 0).direction = RailType::LeftNW;
        grid.Get(2, 0).direction = RailType::StraightWE;
        grid.Get(1, 0).direction = RailType::StraightWE;

        auto gridE = CreateEntity(Maize::Vec2f(0, 0), true, false, grid);

        CreateEntity(CartesianToPixel(0, 1, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(0, 2, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(0, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(1, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(3, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(3, 2, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(3, 1, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(3, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(1, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));

        CreateEntity(CartesianToPixel(0, 1, 32, 32), false, false,
            Maize::SpriteRenderer(sprite),
            RailController(CartesianToPixel(0, 1, 32, 32), gridE)
        );

        AddSystem<Maize::Position, RailController>("Rail Controller", flecs::OnUpdate, Move);
    }

    virtual void OnEnd() override {}

private:
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Texture> textureRed;
};
