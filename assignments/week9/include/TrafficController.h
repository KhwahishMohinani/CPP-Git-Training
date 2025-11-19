#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include <vector>
#include <mutex>
#include "struct.h"

class ILane;

class TrafficController
{
private:
    std::vector<ILane *> lanes;
    bool stop;
    int currentGreenIndex;
    std::mutex mutex;

public:
    TrafficController(std::vector<ILane *> &lanesVector);
    int getCurrentGreenIndex();
    void runController();
    void stopController();
    std::string processRequest(const Vehicle &vehicle);
};

#endif
