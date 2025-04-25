#include "PropertyListing.h"
#include "CustomEnums.h"
#include <sstream>
#include <chrono>

PropertyListing::PropertyListing(
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
    const std::string& listing_date_str
)
    : address_line(address_line), town_name(town_name), state(state), zipcode(zipcode),
    size(size), lot_size(lot_size), number_of_bed(number_of_bed), number_of_bath(number_of_bath),
    year_built(year_built), price(price), days_on_market(days_on_market),
    property_type(property_type), sale_status(sale_status)
{
    // Parse the date string (assuming format: YYYY-MM-DD)
    int y, m, d;
    char delimiter;
    std::istringstream date_stream(listing_date_str);

    date_stream >> y >> delimiter >> m >> delimiter >> d;

    // Create the year_month_day object
    listing_date = std::chrono::year_month_day{
        std::chrono::year(y),
        std::chrono::month(m),
        std::chrono::day(d)
    };
}

double PropertyListing::pricePerSqFt() const {
    if (size == 0) return 0.0;
    return static_cast<double>(price) / size;
}

std::string PropertyListing::propertyTypeToString() const {
    switch (property_type) {
    case PropertyType::SingleFamily: return "SingleFamily";
    case PropertyType::Condo: return "Condo";
    case PropertyType::Apartment: return "Apartment";
    default: return "Unknown";
    }
}

std::string PropertyListing::saleStatusToString() const {
    switch (sale_status) {
    case SaleStatus::Active: return "Active";
    case SaleStatus::Sold: return "Sold";
    case SaleStatus::Pending: return "Pending";
    default: return "Unknown";
    }
}

std::string PropertyListing::listingDateToString() const {
    return std::to_string(static_cast<int>(listing_date.year())) + "-" +
        std::to_string(static_cast<unsigned>(listing_date.month())) + "-" +
        std::to_string(static_cast<unsigned>(listing_date.day()));
}