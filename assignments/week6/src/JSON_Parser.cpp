#include "JSON_Parser.h"
#include "constants.h"
#include <fstream>
#include <iostream>

void JSON_Parser::print() const
{
    std::cout << json.dump(2) << "\n";
}

bool JSON_Parser::parse(const std::string &filename)
{
    bool success = false;
    try
    {
        std::ifstream file(filename);
        file >> json;
        success = true;
    }
    catch (const std::exception &exception)
    {
        std::cout << JSON_PARSING_ERROR;
    }
    return success;
}
