#pragma once

namespace Maize
{
    class Renderer;

    namespace Internal
    {
        struct RenderingContext
        {
            Renderer* renderer = nullptr;

            RenderingContext() = default;

            RenderingContext(Renderer* renderer) : renderer(renderer) { }
        };
    } // Internal
} // Maize