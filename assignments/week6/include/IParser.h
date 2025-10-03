#ifndef IPARSER_H
#define IPARSER_H

#include <vector>
#include <string>

class IParser
{
protected:
    std::string parserName;

public:
    virtual bool parse(const std::string &filename) = 0;
    virtual void print() const = 0;
    virtual ~IParser() {}
};

#endif
