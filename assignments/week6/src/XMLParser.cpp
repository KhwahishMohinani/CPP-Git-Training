#include "XMLParser.h"
#include "constants.h"
#include <fstream>
#include <stdexcept>

using namespace tinyxml2;

XMLParser::XMLParser() : IParser("XML") {}

std::string XMLParser::getChildText(tinyxml2::XMLElement *parent, const char *name)
{
    std::string result;

    if (parent)
    {
        XMLElement *child = parent->FirstChildElement(name);
        if (child)
        {
            const char *text = child->GetText();
            if (text)
                result = text;
        }
    }

    return result;
}

void XMLParser::parse(const std::string &filename)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename.c_str());
    if (error != tinyxml2::XML_SUCCESS)
        throw std::runtime_error(ERROR_OPENING_XML_FILE);

    XMLElement *root = doc.RootElement();
    if (!root)
        throw std::runtime_error(NO_ROOT_ELEMENT_FOUND);

    data.clear();
    for (XMLElement *belem = root->FirstChildElement(BOOK_LABEL); belem; belem = belem->NextSiblingElement(BOOK_LABEL))
    {
        Data d;
        int id = 0;
        belem->QueryIntAttribute(COL_ID, &id);
        d.id = id;

        d.title = getChildText(belem, COL_TITLE);
        d.author = getChildText(belem, COL_AUTHOR);
        std::string yearStr = getChildText(belem, COL_YEAR);
        std::string priceStr = getChildText(belem, COL_PRICE);

        try
        {
            d.year = !yearStr.empty() ? std::stoi(yearStr) : 0;
        }
        catch (...)
        {
            d.year = 0;
        }
        try
        {
            d.price = !priceStr.empty() ? std::stod(priceStr) : 0.0;
        }
        catch (...)
        {
            d.price = 0.0;
        }

        data.push_back(d);
    }
}

std::vector<Data> XMLParser::getData() const
{
    return data;
}
