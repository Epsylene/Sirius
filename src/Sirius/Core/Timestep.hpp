
#pragma once

namespace Sirius
{
    class Timestep
    {
        private:

            float time;

        public:

            constexpr Timestep(float time = 0.f): time(time)
            {}

            float getSeconds() const { return time; }
            float getMilliSeconds() const { return time * 1000.f; }

            constexpr operator float() const { return time; }
    };
}
