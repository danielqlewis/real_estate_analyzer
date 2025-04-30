#pragma once

#include <vector>
#include <functional>
#include <chrono>
#include "PropertyListing.h"

class PropertyFilter {
public:
    using FilterFunction = std::function<bool(const PropertyListing&)>;

    // Add a filter criteria to the filter collection
    void addFilter(FilterFunction filter);

    // Apply all filters to a collection of properties
    std::vector<PropertyListing> apply(const std::vector<PropertyListing>& properties) const;

    // Clear all filters
    void clearFilters();

    // Factory methods for common filter types
    static FilterFunction minSize(int minSize);
    static FilterFunction maxSize(int maxSize);
    static FilterFunction minLotSize(int minSize);
    static FilterFunction maxLotSize(int maxSize);
    static FilterFunction maxPrice(int maxPrice);
    static FilterFunction minPrice(int minPrice);
    static FilterFunction priceBetween(int minPrice, int maxPrice);
    static FilterFunction minDaysOnMarket(int days);
    static FilterFunction maxDaysOnMarket(int days);
    static FilterFunction minYearBuilt(int minYear);
    static FilterFunction maxYearBuilt(int maxYear);
    static FilterFunction yearBuiltBetween(int minYear, int maxYear);
    static FilterFunction inTown(const std::string& townName);
    static FilterFunction inState(const std::string& state);
    static FilterFunction inZipcode(const std::string& zipcode);
    static FilterFunction hasPropertyType(PropertyType type);
    static FilterFunction hasSaleStatus(SaleStatus status);
    static FilterFunction listedAfter(const std::chrono::year_month_day& date);
    static FilterFunction listedBefore(const std::chrono::year_month_day& date);
    static FilterFunction listedBetween(const std::chrono::year_month_day& startDate,
        const std::chrono::year_month_day& endDate);
    static FilterFunction bedroomsAtLeast(int num);
    static FilterFunction bedroomsAtMost(int num);
    static FilterFunction bathroomsAtLeast(int num);
    static FilterFunction bathroomsAtMost(int num);

    size_t getFilterCount() const {
        return filters.size();
    }

    bool removeFilterByIndex(size_t index);

private:
    std::vector<FilterFunction> filters;
};