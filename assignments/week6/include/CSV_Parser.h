#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "IParser.h"
#include "rapidcsv.h"

class CSV_Parser : public IParser
{
private:
    rapidcsv::Document document;
    bool verifyDocument() const;

public:
    bool parse(const std::string &filename);
    void print() const;
};

#endif
