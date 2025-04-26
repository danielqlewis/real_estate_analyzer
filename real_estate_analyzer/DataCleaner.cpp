#include "DataCleaner.h"
#include <fstream>
#include <iostream>
#include "CsvReader.h"
#include "CsvWriter.h"

bool DataCleaner::cleanData(const std::string& inputFile, const std::string& outputFile) {
    // Stand-in implementation: just read and write without cleaning
    try {
        // Read the input file
        std::vector<PropertyListing> properties = CsvReader::readPropertiesFromFile(inputFile);

        // In the real implementation, we would apply cleaning rules here

        // Write the cleaned data to the output file
        return CsvWriter::writePropertiesToFile(properties, outputFile);
    }
    catch (const std::exception& e) {
        std::cerr << "Error cleaning data: " << e.what() << std::endl;
        return false;
    }
}

std::vector<PropertyListing> DataCleaner::processRawData(const std::vector<std::string>& rawData) {
    // Stand-in implementation: just parse the data as-is
    std::vector<PropertyListing> properties;

    // Skip header row (first element)
    for (size_t i = 1; i < rawData.size(); ++i) {
        try {
            PropertyListing property = CsvReader::parsePropertyLine(rawData[i]);
            properties.push_back(property);
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
            // Continue to next line
        }
    }

    return properties;
}