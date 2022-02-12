
#pragma once

int main()
{
    auto app = Sirius::createApplication();
    app->run();

    Sirius::Log::log(Sirius::LogLevel::TRACE, Sirius::LogChannel::CORE,
                     "{}, {}", 1, 2);

    return 0;
}
