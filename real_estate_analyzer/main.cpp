#include "PropertyListing.h"
#include "CsvWriter.h"
#include <iostream>
#include <vector>

int main() {
    // Create sample property listings
    PropertyListing listing1(
        "123 Main St",
        "Springfield",
        "IL",
        "62701",
        2000, // square feet
        5000, // lot size
        3, // bedrooms
        2, // bathrooms
        1990, // year built
        250000, // price
        45, // days on market
        PropertyType::SingleFamily,
        SaleStatus::Active,
        "2025-04-24" // listing date
    );

    PropertyListing listing2(
        "456 Oak Ave",
        "Springfield",
        "IL",
        "62702",
        1500, // square feet
        3000, // lot size
        2, // bedrooms
        1, // bathrooms
        2005, // year built
        199000, // price
        30, // days on market
        PropertyType::Condo,
        SaleStatus::Pending,
        "2025-04-10" // listing date
    );

    PropertyListing listing3(
        "789 Pine Blvd",
        "Capital City",
        "IL",
        "62704",
        3200, // square feet
        8000, // lot size
        4, // bedrooms
        3, // bathrooms
        2020, // year built
        450000, // price
        15, // days on market
        PropertyType::SingleFamily,
        SaleStatus::Sold,
        "2025-03-15" // listing date
    );

    // Create a vector and add the listings
    std::vector<PropertyListing> listings;
    listings.push_back(listing1);
    listings.push_back(listing2);
    listings.push_back(listing3);

    // Write the vector to a CSV file
    bool success = CsvWriter::writePropertiesToFile(listings, "properties.csv");

    if (success) {
        std::cout << "Properties written to CSV successfully!" << std::endl;
        std::cout << "Wrote " << listings.size() << " properties to file." << std::endl;
    }
    else {
        std::cout << "Failed to write properties to CSV." << std::endl;
    }

    return 0;
}