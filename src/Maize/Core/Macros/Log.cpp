#include "Maize/Core/Macros/Log.h"

#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace Maize
{
    void Log::Initialise()
    {
        // prevent application from crashing if this gets called multiple times
        static bool initialised = false;
        if (initialised) return;
        initialised = true;

        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stderr_color_mt("Maize");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_GameLogger = spdlog::stderr_color_mt("Game");
        s_GameLogger->set_level(spdlog::level::trace);
    }
} // Maize
