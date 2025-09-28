#ifndef IPARSER_H
#define IPARSER_H

#include <vector>
#include <string>
#include "struct.h"

class IParser
{
protected:
    std::string parserName;

public:
    IParser(const std::string &name) : parserName(name) {}
    std::string getParserName() const { return parserName; }
    virtual void parse(const std::string &filename) = 0;
    virtual std::vector<Data> getData() const = 0;
    virtual ~IParser() {}
};

#endif
