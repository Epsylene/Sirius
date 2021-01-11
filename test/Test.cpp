
#include "Sirius.h"

class Test: public Sirius::Simulation
{
    public:

        Test()
        {

        }
};

Sirius::Simulation* Sirius::createSimulation()
{
    return new Test();
}
