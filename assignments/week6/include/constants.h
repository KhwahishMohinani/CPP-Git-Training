#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const std::string XML_FILE = "./dataFiles/data.xml";
const std::string CSV_FILE = "./dataFiles/data.csv";
const std::string JSON_FILE = "./dataFiles/data.json";

const char COL_ID[] = "id";
const char COL_TITLE[] = "title";
const char COL_AUTHOR[] = "author";
const char COL_YEAR[] = "year";
const char COL_PRICE[] = "price";
const char BOOK_LABEL[] = "book";
const char CATALOG[] = "catalog";

const std::string INVALID_CHOICE = "Invalid choice.\n";
const std::string USING_PARSER = "Using parser: ";
const std::string INPUT_MENU = "Choose parser:\n1. XML\n2. CSV\n3. JSON\nChoice: ";
const std::string ERROR = "Error: ";
const std::string NO_BOOKS_FOUND = "No books found.\n";
const std::string ERROR_OPENING_JSON_FILE = "Cannot open JSON file: ";
const std::string ERROR_OPENING_XML_FILE = "Failed to load XML file";
const std::string ERROR_OPENING_CSV_FILE = "Cannot open CSV file: ";
const std::string CSV_PARSING_ERROR = "CSV parsing error: ";
const std::string MISSING_CATALOG = "Invalid JSON format: missing 'catalog'";
const std::string NO_ROOT_ELEMENT_FOUND = "XML has no root element";

const int DEFAULT_ID = 0;
const std::string DEFAULT_TITLE = "";
const std::string DEFAULT_AUTHOR = "";
const int DEFAULT_YEAR = 0;
const double DEFAULT_PRICE = 0.0;

#endif
