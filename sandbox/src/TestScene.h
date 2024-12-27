#pragma once

#include <Maize.h>

/**
 * Direction layout in binary.
 */
namespace RailDir
{
    enum
    {
        None = 0, // 00000000
        N    = 1, // 00000001
        E    = 2, // 00000010
        S    = 4, // 00000100
        W    = 8, // 00001000
    };

    inline std::string_view RailDirToStr(uint8_t dir)
    {
        switch (dir)
        {
            case None: return "None";
            case N:    return "N";
            case E:    return "E";
            case S:    return "S";
            case W:    return "W";
            default:   return "Unknown";
        }
    }
} // RailDir

/**
 * Bitsets that defines the rail type by possible i/o.
 */
namespace RailType
{
    enum
    {
        None       = RailDir::None,            // No direction (00000000)

        Vertical   = RailDir::N  | RailDir::S, // (i: north, o: south) | (i: south, o: north) (00000101)
        Horizontal = RailDir::W  | RailDir::E, // (i: west,  o: east)  | (i: east,  o: west)  (00001010)

        NorthRight = RailDir::N  | RailDir::E, // (i: north, o: east)  | (i: east,  o: south) (00000011)
        NorthLeft  = RailDir::N  | RailDir::W, // (i: north, o: west)  | (i: west,  o: south) (00001001)

        SouthRight = RailDir::S  | RailDir::E, // (i: south, o: east)  | (i: east,  o: north) (00000110)
        SouthLeft  = RailDir::S  | RailDir::W, // (i: south, o: west)  | (i: west,  o: north) (00001100)
    };

    inline std::string_view RailTypeToStr(uint8_t type)
    {
        switch (type)
        {
            case None:       return "None";
            case Vertical:   return "Vertical";
            case Horizontal: return "Horizontal";
            case NorthRight: return "North Right";
            case NorthLeft:  return "North Left";
            case SouthRight: return "South Right";
            case SouthLeft:  return "South Left";
            default:         return "Unknown";
        }
    }
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
    float speed = 50.0f;

    Maize::Vec2f lastPos;
    Maize::Vec2f nextPos;
    float currentTime = 0.0f;
    uint8_t currentDir = RailDir::N;

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

static float Lerp(float a, float b, float t) { t = std::clamp(t, 0.0f, 1.0f); return a + (b - a) * t; }

static Maize::Vec2f Lerp(Maize::Vec2f from, Maize::Vec2f to, float time)
{
    const float newX = Lerp(from.x, to.x, time);
    const float newY = Lerp(from.y, to.y, time);

    return Maize::Vec2f(newX, newY);
}

static Maize::Vec2i CalculateOffsetForDirection(uint8_t& controllerDirection, Maize::Vec2i offset, int deltaX, int deltaY, uint8_t newControllerDirection = 0)
{
    offset.x += deltaX;
    offset.y += deltaY;

    if (newControllerDirection != 0)
    {
        controllerDirection = newControllerDirection;
    }

    return offset;
}

static Maize::Vec2i GetVerticalOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1);
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1);

    return offset;
}

static Maize::Vec2i GetHorizontalOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0);

    return offset;
}

static Maize::Vec2i GetNorthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0, RailDir::E);
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1, RailDir::S);

    return offset;
}

static Maize::Vec2i GetNorthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::N) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0, RailDir::W);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, 0, -1, RailDir::S);

    return offset;
}

static Maize::Vec2i GetSouthRightOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, 1, 0, RailDir::E);
    if (controllerDirection == RailDir::E) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1, RailDir::N);

    return offset;
}

static Maize::Vec2i GetSouthLeftOffset(uint8_t& controllerDirection, Maize::Vec2i offset)
{
    if (controllerDirection == RailDir::S) return CalculateOffsetForDirection(controllerDirection, offset, -1, 0, RailDir::W);
    if (controllerDirection == RailDir::W) return CalculateOffsetForDirection(controllerDirection, offset, 0, 1, RailDir::N);

    return offset;
}

static Maize::Vec2i GetDirectionOffset(uint8_t direction, uint8_t& controllerDirection, Maize::Vec2i offset)
{
    switch (direction)
    {
        case RailType::Vertical:   return GetVerticalOffset(controllerDirection, offset);
        case RailType::Horizontal: return GetHorizontalOffset(controllerDirection, offset);
        case RailType::NorthRight: return GetNorthRightOffset(controllerDirection, offset);
        case RailType::NorthLeft:  return GetNorthLeftOffset(controllerDirection, offset);
        case RailType::SouthRight: return GetSouthRightOffset(controllerDirection, offset);
        case RailType::SouthLeft:  return GetSouthLeftOffset(controllerDirection, offset);
        case RailType::None:       return Maize::Vec2i{-1, -1};
        default:                   GAME_ASSERT(false, "Unknown direction");
    }

    return offset;
}

static void HandleDirection(Grid& grid, RailController& controller, Maize::Vec2f& nextPosition, Maize::Vec2f& lastPosition)
{
    const Maize::Vec2i gridPos = PixelToCartesian(nextPosition.x, nextPosition.y, 32, 32);
    const auto& tile = grid.Get(gridPos.x, gridPos.y);
    const Maize::Vec2i gridPosOffset = GetDirectionOffset(tile.direction, controller.currentDir, gridPos);

    if (gridPosOffset == Maize::Vec2i(-1, -1)) return;

    const uint8_t nextDirection = grid.Get(gridPosOffset.x, gridPosOffset.y).direction;

    if ((controller.currentDir & nextDirection) == 0) return;

    if (nextDirection != RailType::None)
    {
        lastPosition = nextPosition;
        nextPosition = CartesianToPixel(gridPosOffset.x, gridPosOffset.y, 32, 32);
        controller.currentTime = 0.0f;
    }
}

static bool Approx(float a, float b)
{
    return std::abs(a - b) < std::numeric_limits<float>::epsilon();
}

static bool Approx(Maize::Vec2f a, Maize::Vec2f b)
{
    return Approx(a.x, b.x) && Approx(a.y, b.y);
}

static void Move(Maize::SystemState s, Maize::Entity e, Maize::Position& position, RailController& controller)
{
    auto* input = s.GetSingleton<Maize::Input>();

    if (input->GetButtonHeld(Maize::KeyCode::W))
    {
        if (auto* grid = controller.grid.TryGetMutComponent<Grid>())
        {
            if (Approx(position, controller.nextPos))
            {
                HandleDirection(*grid, controller, controller.nextPos, controller.lastPos);
            }
        }

        controller.currentTime += controller.speed * s.DeltaTime();
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
        grid.Set(0, 3, { RailType::NorthRight }); grid.Set(1, 3, { RailType::Horizontal }); grid.Set(2, 3, { RailType::NorthRight });
        grid.Set(0, 2, { RailType::Vertical });                                                                grid.Set(2, 2, { RailType::Vertical });
        grid.Set(0, 1, { RailType::Vertical });                                                                grid.Set(2, 1, { RailType::Vertical });
        grid.Set(0, 0, { RailType::SouthLeft }); grid.Set(1, 0, { RailType::Horizontal });  grid.Set(2, 0, { RailType::SouthLeft });

        CreateEntity(CartesianToPixel(0, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(0, 1, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(0, 2, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(0, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(1, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(1, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 3, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 2, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 1, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));
        CreateEntity(CartesianToPixel(2, 0, 32, 32), true, false, Maize::SpriteRenderer(spriteRed));


        auto gridE = CreateEntity(Maize::Vec2f(0, 0), true, false, grid);

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
