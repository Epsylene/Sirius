
#include "Sirius/Core/Log.hpp"

namespace Sirius
{
    Ref<spdlog::logger> Log::coreLogger;
    Ref<spdlog::logger> Log::clientLogger;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        coreLogger = spdlog::stdout_color_mt("SIRIUS");
        coreLogger->set_level(spdlog::level::trace);

        clientLogger = spdlog::stdout_color_mt("APP");
        clientLogger->set_level(spdlog::level::trace);
    }
}
