#include "PropertyListing.h"
#include "CsvWriter.h"
#include "CsvReader.h"
#include <iostream>
#include <vector>

int main() {
    // Create sample property listings
    PropertyListing listing1(
        "123 Main St",
        "Springfield",
        "IL",
        "62701",
        2000,
        5000,
        3,
        2,
        1990,
        250000,
        45,
        PropertyType::SingleFamily,
        SaleStatus::Active,
        "2025-04-24"
    );

    PropertyListing listing2(
        "456 Oak Ave",
        "Springfield",
        "IL",
        "62702",
        1500,
        3000,
        2,
        1,
        2005,
        199000,
        30,
        PropertyType::Condo,
        SaleStatus::Pending,
        "2025-04-10"
    );

    PropertyListing listing3(
        "789 Pine Blvd",
        "Capital City",
        "IL",
        "62704",
        3200,
        8000,
        4,
        3,
        2020,
        450000,
        15,
        PropertyType::SingleFamily,
        SaleStatus::Sold,
        "2025-03-15"
    );

    // Create a vector and add the listings
    std::vector<PropertyListing> listings;
    listings.push_back(listing1);
    listings.push_back(listing2);
    listings.push_back(listing3);

    // Write the vector to a CSV file
    std::string filename = "properties.csv";
    bool success = CsvWriter::writePropertiesToFile(listings, filename);

    if (success) {
        std::cout << "Properties written to CSV successfully!" << std::endl;
        std::cout << "Wrote " << listings.size() << " properties to file." << std::endl;

        // Now read the properties back
        std::vector<PropertyListing> readListings = CsvReader::readPropertiesFromFile(filename);

        std::cout << "Read " << readListings.size() << " properties from file." << std::endl;

        // Display the first property to verify
        if (!readListings.empty()) {
            PropertyListing& first = readListings[0];
            std::cout << "First property: " << first.getAddressLine()
                << ", " << first.getTownName()
                << " - $" << first.getPrice() << std::endl;
        }
    }
    else {
        std::cout << "Failed to write properties to CSV." << std::endl;
    }

    return 0;
}