#ifndef STRUCT_H
#define STRUCT_H

#include <string>

struct Data
{
    int id;
    std::string title;
    std::string author;
    int year = 0;
    double price = 0.0;
};

#endif
