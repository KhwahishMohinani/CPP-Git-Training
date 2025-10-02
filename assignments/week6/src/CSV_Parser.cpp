#include "CSV_Parser.h"
#include "constants.h"

void CSV_Parser::print() const
{
    std::vector<std::string> columns = document.GetColumnNames();
    for (std::string column : columns)
        std::cout << column << "\t";
    std::cout << "\n";

    for (size_t row = 0; row < document.GetRowCount(); ++row)
    {
        for (const std::string &column : columns)
            std::cout << document.GetCell<std::string>(column, row) << "\t";
        std::cout << "\n";
    }
}

bool CSV_Parser::verifyDocument() const
{
    bool success = true;
    size_t rowCount = document.GetRowCount();
    size_t columnCount = document.GetColumnCount();

    if (rowCount == 0 || columnCount == 0)
    {
        std::cout << CSV_PARSING_ERROR << EMPTY_CSV;
        success = false;
    }
    else
    {
        bool unevenColumnsDetected = false;

        for (size_t col = 0; col < columnCount && !unevenColumnsDetected; ++col)
        {
            for (size_t row = 0; row < rowCount; ++row)
            {
                try
                {
                    document.GetCell<std::string>(col, row);
                }
                catch (const std::out_of_range &)
                {
                    std::cout << CSV_PARSING_ERROR << UNEVEN_COLUMNS;
                    unevenColumnsDetected = true;
                    success = false;
                    break;
                }
            }
        }
    }

    return success;
}

bool CSV_Parser::parse(const std::string &filename)
{
    bool success = false;

    try
    {
        document.Load(filename, rapidcsv::LabelParams());

        if (verifyDocument())
        {
            success = true;
        }
    }
    catch (const std::exception &exception)
    {
        std::cout << CSV_PARSING_ERROR << exception.what() << "\n";
        success = false;
    }

    return success;
}
