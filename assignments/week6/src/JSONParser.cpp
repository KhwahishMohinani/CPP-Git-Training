#include "JSONParser.h"
#include "constants.h"
#include <fstream>
#include <stdexcept>

JSONParser::JSONParser() : IParser("JSON") {}

void JSONParser::parse(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        throw std::runtime_error(ERROR_OPENING_JSON_FILE + filename);

    nlohmann::json j;
    ifs >> j;

    data.clear();
    if (!j.contains(CATALOG) || !j[CATALOG].is_array())
        throw std::runtime_error(MISSING_CATALOG);

    for (const nlohmann::json &book : j[CATALOG])
    {
        Data d;
        try
        {
            d.id = book.value(COL_ID, DEFAULT_ID);
        }
        catch (...)
        {
            d.id = DEFAULT_ID;
        }
        try
        {
            d.title = book.value(COL_TITLE, DEFAULT_TITLE);
        }
        catch (...)
        {
            d.title = DEFAULT_TITLE;
        }
        try
        {
            d.author = book.value(COL_AUTHOR, DEFAULT_AUTHOR);
        }
        catch (...)
        {
            d.author = DEFAULT_AUTHOR;
        }
        try
        {
            d.year = book.value(COL_YEAR, DEFAULT_YEAR);
        }
        catch (...)
        {
            d.year = DEFAULT_YEAR;
        }
        try
        {
            d.price = book.value(COL_PRICE, DEFAULT_PRICE);
        }
        catch (...)
        {
            d.price = DEFAULT_PRICE;
        }

        data.push_back(d);
    }
}

std::vector<Data> JSONParser::getData() const
{
    return data;
}
