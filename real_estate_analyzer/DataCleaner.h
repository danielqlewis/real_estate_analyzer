#pragma once

#include <string>
#include <vector>
#include "PropertyListing.h"

class DataCleaner {
public:
    // Read raw data from input file, clean it, and write to output file
    static bool cleanData(const std::string& inputFile, const std::string& outputFile);

    // Process a vector of raw property data and return cleaned PropertyListing objects
    static std::vector<PropertyListing> processRawData(const std::vector<std::string>& rawData);

    // For now, this is just a placeholder that passes through data without cleaning
    // Later, it will contain the actual cleaning logic
private:
    // Private helper methods will go here
};