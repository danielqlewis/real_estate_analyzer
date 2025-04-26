#include "PropertyListing.h"
#include "CsvWriter.h"
#include "CsvReader.h"
#include "PropertyFilter.h"
#include "DataCleaner.h"
#include <iostream>
#include <vector>
#include <chrono>

int main() {
    // Test the data cleaning pipeline
    std::string inputFile = "synthetic_property_data.csv";
    std::string cleanedFile = "cleaned_property_data.csv";

    std::cout << "Testing data cleaning pipeline..." << std::endl;
    bool cleaningSuccess = DataCleaner::cleanData(inputFile, cleanedFile);

    if (cleaningSuccess) {
        std::cout << "Data cleaning successful!" << std::endl;

        // Read the cleaned data
        std::vector<PropertyListing> properties = CsvReader::readPropertiesFromFile(cleanedFile);
        std::cout << "Read " << properties.size() << " properties from cleaned file." << std::endl;

        // Test the filtering system
        PropertyFilter filter;

        // Example: Filter for properties with at least 3 bedrooms and priced under $400,000
        filter.addFilter(PropertyFilter::bedroomsAtLeast(3));
        filter.addFilter(PropertyFilter::maxPrice(400000));

        // Apply the filters
        std::vector<PropertyListing> filteredProperties = filter.apply(properties);

        std::cout << "Found " << filteredProperties.size() << " properties matching the criteria." << std::endl;

        // Display some of the filtered properties
        std::cout << "\nFiltered properties:" << std::endl;
        for (size_t i = 0; i < std::min(filteredProperties.size(), size_t(5)); ++i) {
            const PropertyListing& property = filteredProperties[i];
            std::cout << property.getAddressLine() << ", " << property.getTownName()
                << " - $" << property.getPrice() << " - "
                << property.getNumberOfBed() << " beds, "
                << property.getNumberOfBath() << " baths" << std::endl;
        }
    }
    else {
        std::cout << "Data cleaning failed." << std::endl;
    }

    return 0;
}