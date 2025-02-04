#pragma once

namespace Maize
{
    template<typename T>
    struct Rect
    {
        T x = 0;
        T y = 0;
        T width = 0;
        T height = 0;

        constexpr Rect() = default;

        constexpr Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
        {
        }

        constexpr std::string ToString() const
        {
            return "Rect(" +
                std::to_string(x) + ", " +
                std::to_string(y) + ", " +
                std::to_string(width) + ", " +
                std::to_string(height) + ")";
        }

        template<typename U>
        constexpr explicit Rect(const Rect<U>& other)
            : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), width(static_cast<T>(other.width)),
              height(static_cast<T>(other.height))
        {
        }

        template<typename U>
        bool operator==(const Rect<U>& other) const
        {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        template<typename U>
        bool operator!=(const Rect<U>& other) const
        {
            return !(*this == other);
        }
    };

    typedef Rect<float> FloatRect;
    typedef Rect<int32_t> IntRect;
    typedef Rect<uint32_t> UIntRect;
} // Maize
