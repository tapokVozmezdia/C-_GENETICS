#include "simulation.hpp"

int main()
{
    Simulation sim(1440, 960);

    sim.spawn_populus(10);
    sim.run();

    return 0;
}