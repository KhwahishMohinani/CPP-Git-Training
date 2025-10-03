#include "IParser.h"
#include "CSV_Parser.h"
#include "JSON_Parser.h"
#include "XML_Parser.h"
#include "constants.h"

bool validateFile(std::string filename)
{
    bool ifFileExists = false;
    std::ifstream file(filename);
    if (file.is_open())
        ifFileExists = true;
    return ifFileExists;
}

int main()
{
    IParser *parser = nullptr;
    std::string filename;

    std::cout << ENTER_FILE_NAME;
    std::cin >> filename;

    if (!validateFile(filename))
    {
        std::cout << FILE_NOT_EXISTS;
    }
    else
    {
        if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".xml")
        {
            parser = new XML_Parser();
        }
        else if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".csv")
        {
            parser = new CSV_Parser();
        }
        else if (filename.size() >= 5 && filename.substr(filename.size() - 5) == ".json")
        {
            parser = new JSON_Parser();
        }
        else
        {
            std::cout << UNSUPPORTED_FILE_TYPE;
        }

        if (parser && parser->parse(filename))
        {
            parser->print();
        }
        else
        {
            std::cerr << PARSING_FAILED << filename << "\n";
        }
    }

    delete parser;
    parser = nullptr;
}
