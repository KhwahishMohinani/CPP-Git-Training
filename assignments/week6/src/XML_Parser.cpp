#include "XML_Parser.h"
#include "constants.h"
#include <iostream>

bool XML_Parser::parse(const std::string &filename)
{
    bool success = true;
    tinyxml2::XMLError result = document.LoadFile(filename.c_str());
    if (result != tinyxml2::XML_SUCCESS)
    {
        success = false;
        std::cout << XML_PARSING_ERROR;
    }
    return success;
}

void XML_Parser::print() const
{
    tinyxml2::XMLPrinter printer;
    document.Print(&printer);
    std::cout << printer.CStr() << "\n";
}
