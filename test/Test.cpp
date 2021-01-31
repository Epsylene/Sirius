
#include "Sirius.h"

class Test: public Sirius::Simulation
{
    public:

        Test()
        {
            Sirius::Vector2f vec {1, 2};
            Sirius::Vector2f vec2 {0, 1};
            // vec *= 2.f;
            vec = vec2 * 2.f;
            vec = 2.f * vec2;
            std::cout << vec << ", " << vec.getMag() << "\n";
            std::cout << vec2 << ", " << vec2.getMag() << "\n";
        }
};

Sirius::Simulation* Sirius::createSimulation()
{
    return new Test();
}
