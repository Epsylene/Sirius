
#pragma once

int main()
{
    auto simulation = Sirius::createSimulation();
    simulation->run();
    delete simulation;

    return 0;
}
