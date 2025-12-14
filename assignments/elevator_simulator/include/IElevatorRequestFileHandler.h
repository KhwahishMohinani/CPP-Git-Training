#ifndef I_ELEVATOR_REQUEST_FILE_HANDLER_H
#define I_ELEVATOR_REQUEST_FILE_HANDLER_H

#include "ElevatorRequest.h"

class IElevatorRequestFileHandler
{
public:
    virtual bool readNextRequest(ElevatorRequest &request) = 0;
};

#endif
