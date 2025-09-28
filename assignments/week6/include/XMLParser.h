#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "IParser.h"
#include "tinyxml2.h"

class XMLParser : public IParser
{
private:
    std::vector<Data> data;
    std::string getChildText(tinyxml2::XMLElement *parent, const char *name);

public:
    XMLParser();
    void parse(const std::string &filename);
    std::vector<Data> getData() const;
};

#endif
