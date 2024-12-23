#pragma once

namespace Maize
{
    class SpatialHashGrid;

    namespace Internal
    {
        class Renderer;

        struct RenderingContext
        {
            Renderer* renderer = nullptr;
            SpatialHashGrid* spatialIndex = nullptr;

            RenderingContext() = default;

            RenderingContext(Renderer* renderer, SpatialHashGrid* spatialIndex) :
                renderer(renderer), spatialIndex(spatialIndex) { }
        };
    } // Internal
} // Maize