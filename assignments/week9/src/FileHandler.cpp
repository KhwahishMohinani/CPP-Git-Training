#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileHandler::FileHandler(const std::string &fileName)
    : filename(fileName)
{
}

std::vector<Vehicle> FileHandler::loadVehiclesFromFile()
{
    std::vector<Vehicle> vehicles;
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream stringStream(line);
            std::string id, from, turn;

            if (std::getline(stringStream, id, ',') && std::getline(stringStream, from, ',') && std::getline(stringStream, turn, ','))
            {
                vehicles.push_back({id, from, turn});
            }
        }
        file.close();
    }
    return vehicles;
}

bool FileHandler::saveVehiclesToFile(const std::vector<Vehicle> &vehicles)
{
    bool success = true;

    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open())
    {
        success = false;
    }
    else
    {
        for (const Vehicle &vehicle : vehicles)
        {
            file << vehicle.id << "," << vehicle.fromDirection << "," << vehicle.turnDirection << "\n";

            if (!file)
            {
                success = false;
                break;
            }
        }
    }

    file.close();
    return success;
}
