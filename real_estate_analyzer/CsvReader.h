#pragma once

#include <string>
#include <vector>
#include "PropertyListing.h"

class CsvReader {
public:
    // Read all property listings from a CSV file
    static std::vector<PropertyListing> readPropertiesFromFile(const std::string& filename);

    // Helper function to parse a single line
    static PropertyListing parsePropertyLine(const std::string& line);

private:
    // Helper function to convert string to enum values
    static PropertyType stringToPropertyType(const std::string& str);
    static SaleStatus stringToSaleStatus(const std::string& str);
};
