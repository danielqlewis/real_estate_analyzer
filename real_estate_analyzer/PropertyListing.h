#pragma once

#include <string>
#include <chrono>
#include "CustomEnums.h"

class PropertyListing {
private:
    std::string address_line;
    std::string town_name;
    std::string state;
    std::string zipcode;
    int size;
    int lot_size;
    int number_of_bed;
    int number_of_bath;
    int year_built;
    int price;
    int days_on_market;
    PropertyType property_type;
    SaleStatus sale_status;
    std::chrono::year_month_day listing_date; // Changed from std::string

public:
    PropertyListing(
        const std::string& address_line,
        const std::string& town_name,
        const std::string& state,
        const std::string& zipcode,
        int size,
        int lot_size,
        int number_of_bed,
        int number_of_bath,
        int year_built,
        int price,
        int days_on_market,
        PropertyType property_type,
        SaleStatus sale_status,
        const std::string& listing_date_str // We'll parse this string
    );

    std::string getAddressLine() const { return address_line; }
    std::string getTownName() const { return town_name; }
    std::string getState() const { return state; }
    std::string getZipcode() const { return zipcode; }
    int getSize() const { return size; }
    int getLotSize() const { return lot_size; }
    int getNumberOfBed() const { return number_of_bed; }
    int getNumberOfBath() const { return number_of_bath; }
    int getYearBuilt() const { return year_built; }
    int getPrice() const { return price; }
    int getDaysOnMarket() const { return days_on_market; }
    PropertyType getPropertyType() const { return property_type; }
    SaleStatus getSaleStatus() const { return sale_status; }

    std::string propertyTypeToString() const;
    std::string saleStatusToString() const;
    std::string listingDateToString() const;

    double pricePerSqFt() const;

    // Getters for the properties
    std::chrono::year_month_day getListingDate() const { return listing_date; }
    // Add other getters as needed
};