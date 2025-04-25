#pragma once
#include <string>
#include <vector>
#include "PropertyListing.h"

class CsvWriter {
public:
    // Write a single property listing to a new CSV file
    static bool writePropertyToFile(const PropertyListing& property, const std::string& filename);

    // Write multiple property listings to a new CSV file
    static bool writePropertiesToFile(const std::vector<PropertyListing>& properties, const std::string& filename);
};