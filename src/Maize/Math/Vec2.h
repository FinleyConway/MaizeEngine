#pragma once

namespace Maize
{
    template<typename T>
    struct Vec2
    {
        T x = 0;
        T y = 0;

        constexpr Vec2() = default;

        constexpr Vec2(T x, T y) : x(x), y(y)
        {
        }

        template<typename U>
        constexpr explicit Vec2(const Vec2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
        {
        }

        template<typename U>
        bool operator==(const Vec2<U>& other) const
        {
            return x == other.x && y == other.y;
        }

        template<typename U>
        bool operator!=(const Vec2<U>& other) const
        {
            return !(*this == other);
        }
    };

    typedef Vec2<int32_t> Vec2i;
    typedef Vec2<uint32_t> Vec2u;
    typedef Vec2<float> Vec2f;
} // Maize
