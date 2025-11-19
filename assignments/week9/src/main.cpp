#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "TrafficController.h"
#include "TrafficLight.h"
#include "Lane.h"
#include "FileHandler.h"
#include "constants.h"
#include "ISemaphore.h"
#include "Semaphore.h"

void displayStatus(std::vector<ILane *> &lanes, std::vector<Vehicle> &vehicles, TrafficController &controller)
{
    std::cout << CURRENT_TRAFFIC_LIGHT_STATUS;
    for (ILane *lane : lanes)
        std::cout << "  " << lane->getName() << " -> " << lane->getTrafficLight()->getColor() << " | ";

    std::cout << CAR_STATUS;

    for (std::vector<Vehicle>::iterator iterator = vehicles.begin(); iterator != vehicles.end();)
    {
        std::string status = controller.processRequest(*iterator);
        std::cout << iterator->id << FROM << iterator->fromDirection << " -> " << status << "\n";

        if (status == MOVING)
            iterator = vehicles.erase(iterator);
        else
            ++iterator;
    }

    std::cout << SEPARATOR;
}

int main()
{
    ISemaphore *semaphore = new Semaphore();
    TrafficLight northLight(semaphore), southLight(semaphore), eastLight(semaphore), westLight(semaphore);
    Lane north(NORTH_LABEL, &northLight), south(SOUTH_LABEL, &southLight),
        east(EAST_LABEL, &eastLight), west(WEST_LABEL, &westLight);
    std::vector<ILane *> lanes = {&north, &south, &east, &west};

    TrafficController controller(lanes);
    std::thread controllerThread(&TrafficController::runController, &controller);

    FileHandler fileHandler(FILE_PATH);
    std::vector<Vehicle> vehicles = fileHandler.loadVehiclesFromFile();

    if (vehicles.empty())
    {
        std::cerr << NO_VEHICLES_FOUND;
        controller.stopController();
        controllerThread.join();
    }
    else
    {
        std::cout << STARTING_SIMULATION;

        while (true)
        {
            displayStatus(lanes, vehicles, controller);
            fileHandler.saveVehiclesToFile(vehicles);
            std::this_thread::sleep_for(std::chrono::seconds(5));

            if (vehicles.empty())
            {
                std::cout << ALL_VEHICLES_PASSED;
                break;
            }
        }

        controller.stopController();
        controllerThread.join();

        std::cout << SIMULATION_STOPPED;
    }
    delete semaphore;
}
