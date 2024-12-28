#pragma once

#include "Maize/Math/Math.h"

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

        constexpr Vec2<float> LerpTo(Vec2<float> to, float time)
        {
            const float newX = Math::Lerp(x, to.x, time);
            const float newY = Math::Lerp(y, to.y, time);

            return Vec2(newX, newY);
        }

        constexpr bool ApproxOf(Vec2<float> other)
        {
            return Math::Approx(x, other.x) && Math::Approx(y, other.y);
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

template<typename T>
struct std::hash<Maize::Vec2<T>>
{
    size_t operator()(Maize::Vec2<T> v) const noexcept
    {
        // https://stackoverflow.com/a/55083395
        size_t hash = std::hash<int32_t>()(v.x);
        hash <<= sizeof(size_t) * 4;
        hash ^= std::hash<int32_t>()(v.y);
        return std::hash<size_t>()(hash);
    }
};