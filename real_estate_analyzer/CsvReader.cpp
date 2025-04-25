#include "CsvReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<PropertyListing> CsvReader::readPropertiesFromFile(const std::string& filename) {
    std::vector<PropertyListing> properties;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return properties; // Return empty vector
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        // Skip the header line
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        // Parse the line into a PropertyListing
        try {
            PropertyListing property = parsePropertyLine(line);
            properties.push_back(property);
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
            // Continue to next line
        }
    }

    file.close();
    return properties;
}

PropertyListing CsvReader::parsePropertyLine(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    // Split the line by commas
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    // Make sure we have the right number of tokens
    if (tokens.size() != 14) {
        throw std::runtime_error("Invalid number of fields in CSV line");
    }

    // Parse the tokens into appropriate types
    std::string address_line = tokens[0];
    std::string town_name = tokens[1];
    std::string state = tokens[2];
    std::string zipcode = tokens[3];
    int size = std::stoi(tokens[4]);
    int lot_size = std::stoi(tokens[5]);
    int number_of_bed = std::stoi(tokens[6]);
    int number_of_bath = std::stoi(tokens[7]);
    int year_built = std::stoi(tokens[8]);
    int price = std::stoi(tokens[9]);
    int days_on_market = std::stoi(tokens[10]);
    PropertyType property_type = stringToPropertyType(tokens[11]);
    SaleStatus sale_status = stringToSaleStatus(tokens[12]);
    std::string listing_date = tokens[13];

    // Create and return the PropertyListing
    return PropertyListing(
        address_line,
        town_name,
        state,
        zipcode,
        size,
        lot_size,
        number_of_bed,
        number_of_bath,
        year_built,
        price,
        days_on_market,
        property_type,
        sale_status,
        listing_date
    );
}

PropertyType CsvReader::stringToPropertyType(const std::string& str) {
    if (str == "SingleFamily") return PropertyType::SingleFamily;
    if (str == "Condo") return PropertyType::Condo;
    if (str == "Apartment") return PropertyType::Apartment;
    throw std::runtime_error("Invalid PropertyType: " + str);
}

SaleStatus CsvReader::stringToSaleStatus(const std::string& str) {
    if (str == "Active") return SaleStatus::Active;
    if (str == "Sold") return SaleStatus::Sold;
    if (str == "Pending") return SaleStatus::Pending;
    throw std::runtime_error("Invalid SaleStatus: " + str);
}