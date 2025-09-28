#include "IParser.h"
#include "XMLParser.h"
#include "CSVParser.h"
#include "JSONParser.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <stdexcept>

void displayBooks(const std::vector<Data> &data)
{
    if (data.empty())
    {
        std::cout << NO_BOOKS_FOUND;
        return;
    }

    std::cout << COL_ID << "\t"
              << COL_TITLE << "\t"
              << COL_AUTHOR << "\t"
              << COL_YEAR << "\t"
              << COL_PRICE << "\n";

    for (const Data &d : data)
    {
        std::cout << d.id << "\t"
                  << d.title << "\t"
                  << d.author << "\t"
                  << (d.year == 0 ? "-" : std::to_string(d.year)) << "\t"
                  << d.price << "\n";
    }
}

void runParser(IParser *parser, const std::string &filename)
{
    try
    {
        parser->parse(filename);
        displayBooks(parser->getData());
    }
    catch (const std::exception &ex)
    {
        std::cout << ERROR << ex.what() << "\n";
    }
}

int main()
{
    IParser *parser = nullptr;
    std::string file;

    int choice;
    std::cout << INPUT_MENU;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        parser = new XMLParser();
        file = XML_FILE;
        break;
    case 2:
        parser = new CSVParser();
        file = CSV_FILE;
        break;
    case 3:
        parser = new JSONParser();
        file = JSON_FILE;
        break;
    default:
        std::cout << INVALID_CHOICE;
        return 1;
    }

    std::cout << USING_PARSER << parser->getParserName() << "\n";
    runParser(parser, file);

    delete parser;
    return 0;
}
