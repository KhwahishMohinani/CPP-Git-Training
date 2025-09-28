#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "IParser.h"
#include <vector>
#include <string>

class CSVParser : public IParser
{
private:
    std::vector<Data> data;

public:
    CSVParser();
    void parse(const std::string &filename) override;
    std::vector<Data> getData() const override;
};

#endif
