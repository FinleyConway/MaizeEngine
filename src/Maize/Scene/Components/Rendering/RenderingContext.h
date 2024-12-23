#pragma once

namespace Maize
{
    class Renderer;
    class SpatialHashGrid;

    namespace Internal
    {
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