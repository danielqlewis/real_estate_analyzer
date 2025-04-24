#pragma once
#include <string>
#include "CustomEnums.h"
#include <chrono>
using namespace std::chrono;

class PropertyListing {
public:
    // Constructor
    PropertyListing(
        const std::string& address_line,
        const std::string& town_name,
        const std::string& state,
        const std::string& zipcode,
        int size,
        int lot_size, // in square feet
        int number_of_bed,
        int number_of_bath,
        int year_built,
        int price,
        int days_on_market,
        PropertyType property_type,
        SaleStatus sale_status,
        std::chrono::year_month_day listingDate // we’ll parse to a date later
    );

    // Accessors (optional, if you want encapsulation)
    double pricePerSqFt() const;

private:
    // Basic Info
    std::string address_line;
    std::string town_name;
    std::string state;
    std::string zipcode;

    // Numerical Info
    int size;
    int lot_size;
    int number_of_bed;
    int number_of_bath;
    int year_built;
    int price;
    int days_on_market;

    // Custom Values
    PropertyType property_type;
    SaleStatus sale_status;

    // Date
    std::string listingDate;  // You could later change this to a proper date object
};