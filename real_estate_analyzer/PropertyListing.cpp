#include "PropertyListing.h"

using namespace std::chrono;

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
    int year,
    unsigned int month,
    unsigned int day
)
    : address_line(address_line), town_name(town_name), state(state), zipcode(zipcode),
    size(size), lot_size(lot_size), number_of_bed(number_of_bed), number_of_bath(number_of_bath), year_built(year_built), price(price), days_on_market(days_on_market),
    property_type(property_type), sale_status(sale_status),
    listing_date(year{ year }, month{ month }, day{ day })
{ }

double PropertyListing::pricePerSqFt() const {
    if (size == 0) return 0.0;
    return static_cast<double>(price) / size;
}