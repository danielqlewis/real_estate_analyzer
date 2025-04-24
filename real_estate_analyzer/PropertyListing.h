#pragma once
#include <string>
#include <chrono>
#include "CustomEnums.h"

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
        int year,
        unsigned int month,
        unsigned int day
    );

    // Accessors
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
    std::chrono::year_month_day listing_date;
};