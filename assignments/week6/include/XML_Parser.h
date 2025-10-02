#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "IParser.h"
#include "tinyxml2.h"

class XML_Parser : public IParser
{
private:
    tinyxml2::XMLDocument document;

public:
    bool parse(const std::string &filename);
    void print() const;
};

#endif
