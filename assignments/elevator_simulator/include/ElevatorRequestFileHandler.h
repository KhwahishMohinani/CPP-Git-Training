#ifndef ELEVATOR_REQUEST_FILE_HANDLER_H
#define ELEVATOR_REQUEST_FILE_HANDLER_H

#include "IElevatorRequestFileHandler.h"
#include <string>
#include <fstream>

class ElevatorRequestFileHandler : public IElevatorRequestFileHandler
{
private:
    std::string filename;
    std::ifstream file;

public:
    ElevatorRequestFileHandler(const std::string &fileName);
    bool readNextRequest(ElevatorRequest &request);
};

#endif
