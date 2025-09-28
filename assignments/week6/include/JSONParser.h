#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "IParser.h"
#include <vector>
#include <string>
#include "json.hpp"

class JSONParser : public IParser
{
private:
    std::vector<Data> data;

public:
    JSONParser();
    void parse(const std::string &filename) override;
    std::vector<Data> getData() const override;
};

#endif
