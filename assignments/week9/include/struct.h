#ifndef STRUCT_H
#define STRUCT_H

#include <string>

struct Vehicle
{
    std::string id;
    std::string fromDirection;
    std::string turnDirection;

    bool operator==(const Vehicle &other) const
    {
        return fromDirection == other.fromDirection && turnDirection == other.turnDirection && id == other.id;
    }
};

#endif
