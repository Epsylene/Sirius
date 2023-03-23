
#pragma once

#include "Logger/Logger.hpp"

int main()
{
    Sirius::Logger::init();

    auto app = Sirius::createApplication();
    app->run();

    return 0;
}
