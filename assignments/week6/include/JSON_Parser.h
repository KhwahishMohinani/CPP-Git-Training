#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "IParser.h"
#include "json.hpp"

class JSON_Parser : public IParser
{
private:
    nlohmann::json json;

public:
    bool parse(const std::string &filename);
    void print() const;
};

#endif
