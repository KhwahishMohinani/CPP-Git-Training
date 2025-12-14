#include "ElevatorRequestFileHandler.h"
#include <fstream>
#include <sstream>
#include <thread>

ElevatorRequestFileHandler::ElevatorRequestFileHandler(const std::string &fileName)
    : filename(fileName), file(fileName)
{
}

bool ElevatorRequestFileHandler::readNextRequest(ElevatorRequest &request)
{
    bool success = false;
    std::string line;

    if (std::getline(file, line))
    {
        std::stringstream stringstream(line);
        std::string sourceFloor, direction, destinationFloor, delay;

        bool parsed =
            std::getline(stringstream, sourceFloor, ',') &&
            std::getline(stringstream, direction, ',') &&
            std::getline(stringstream, destinationFloor, ',') &&
            std::getline(stringstream, delay, ',');

        if (parsed)
        {
            try
            {
                request.source = std::stoi(sourceFloor);
                request.direction = direction[0];
                request.destination = std::stoi(destinationFloor);
                request.delay = std::stoi(delay);
            }
            catch (...)
            {
                success = false;
            }
        }

        success = true;
    }

    return success;
}
