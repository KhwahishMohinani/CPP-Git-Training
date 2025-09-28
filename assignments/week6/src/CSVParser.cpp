#include "CSVParser.h"
#include "rapidcsv.h"
#include "constants.h"
#include <fstream>
#include <stdexcept>

CSVParser::CSVParser() : IParser("CSV") {}

void CSVParser::parse(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        throw std::runtime_error(ERROR_OPENING_CSV_FILE + filename);
    ifs.close();

    try
    {
        rapidcsv::Document doc(filename, rapidcsv::LabelParams());
        data.clear();

        for (int i = 0; i < doc.GetRowCount(); ++i)
        {
            Data d;
            try
            {
                d.id = doc.GetCell<int>(COL_ID, i);
            }
            catch (...)
            {
                d.id = DEFAULT_ID;
            }
            try
            {
                d.title = doc.GetCell<std::string>(COL_TITLE, i);
            }
            catch (...)
            {
                d.title = DEFAULT_TITLE;
            }
            try
            {
                d.author = doc.GetCell<std::string>(COL_AUTHOR, i);
            }
            catch (...)
            {
                d.author = DEFAULT_AUTHOR;
            }
            try
            {
                d.year = doc.GetCell<int>(COL_YEAR, i);
            }
            catch (...)
            {
                d.year = DEFAULT_YEAR;
            }
            try
            {
                d.price = doc.GetCell<double>(COL_PRICE, i);
            }
            catch (...)
            {
                d.price = DEFAULT_PRICE;
            }
            data.push_back(d);
        }
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(std::string(CSV_PARSING_ERROR) + e.what());
    }
}

std::vector<Data> CSVParser::getData() const
{
    return data;
}
