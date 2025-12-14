#include "ElevatorSimulator.h"

int main()
{
    ElevatorSimulator simulator("data/ElevatorRequestData.csv");
    simulator.start();
    return 0;
}
