#ifndef VEHICLE_LOADER_H
#define VEHICLE_LOADER_H

#include "struct.h"
#include <vector>
#include <string>

class FileHandler
{
private:
    std::string filename;

public:
    FileHandler(const std::string &fileName);
    std::vector<Vehicle> loadVehiclesFromFile();
    bool saveVehiclesToFile(const std::vector<Vehicle> &vehicles);
};

#endif
