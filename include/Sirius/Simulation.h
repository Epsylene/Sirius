
#pragma once

namespace Sirius
{
    class Simulation
    {
        public:

            Simulation();
            virtual ~Simulation();

            void run();
    };

    Simulation* createSimulation();
}
