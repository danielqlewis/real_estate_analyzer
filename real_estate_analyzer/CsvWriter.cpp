#include "CsvWriter.h"
#include <fstream>
#include <iostream>

bool CsvWriter::writePropertyToFile(const PropertyListing& property, const std::string& filename) {
    // Call the vector version with a single element
    std::vector<PropertyListing> properties = { property };
    return writePropertiesToFile(properties, filename);
}

bool CsvWriter::writePropertiesToFile(const std::vector<PropertyListing>& properties, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    // Write header row
    file << "Address,Town,State,Zip,Size,LotSize,Bedrooms,Bathrooms,YearBuilt,Price,DaysOnMarket,PropertyType,SaleStatus,ListingDate\n";

    // Write each property
    for (const auto& prop : properties) {
        // Write the property data as a CSV row
        file << prop.getAddressLine() << ","
            << prop.getTownName() << ","
            << prop.getState() << ","
            << prop.getZipcode() << ","
            << prop.getSize() << ","
            << prop.getLotSize() << ","
            << prop.getNumberOfBed() << ","
            << prop.getNumberOfBath() << ","
            << prop.getYearBuilt() << ","
            << prop.getPrice() << ","
            << prop.getDaysOnMarket() << ","
            << prop.propertyTypeToString() << ","
            << prop.saleStatusToString() << ","
            << prop.listingDateToString() << "\n";
    }

    file.close();
    return true;
}