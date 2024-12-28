#pragma once

namespace Maize
{
    class Math
    {
    public:
        Math() = delete;

        static float Lerp(float a, float b, float t)
        {
            return a + (b - a) * std::clamp(t, 0.0f, 1.0f);
        }
        
        static bool Approx(float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
        {
            return std::abs(a - b) < epsilon;
        }
    };
} // Maize
