
#include "Sirius/Log.h"

namespace Sirius
{
    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::clientLogger;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        coreLogger = spdlog::stdout_color_mt("SIRIUS");
        coreLogger->set_level(spdlog::level::trace);

        clientLogger = spdlog::stdout_color_mt("APP");
        clientLogger->set_level(spdlog::level::trace);
    }
}
