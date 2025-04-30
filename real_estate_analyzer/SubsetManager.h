#pragma once

#include <vector>
#include <string>
#include "PropertyListing.h"
#include "PropertyFilter.h"
#include "CustomEnums.h"

enum class FilterCategory {
    SaleStatus,
    PropertyType,
    Location,
    BedBaths,
    Size,
    LotSize,
    ListingDate,
    Price,
    DaysOnMarket,
    YearBuilt
};

struct FilterTracker {
    bool saleStatus = false;
    bool propertyType = false;
    bool location = false;
    bool bedBaths = false;
    bool size = false;
    bool lotSize = false;
    bool listingDate = false;
    bool price = false;
    bool daysOnMarket = false;
    bool yearBuilt = false;
};

// Data structure to track filter operations
struct FilterOperation {
    FilterCategory category;
    size_t filterIndex;
    std::string description;  // Human-readable description of the filter
};

class SubsetManager {
private:
    std::vector<PropertyListing> sourceData;
    std::vector<PropertyListing> resultSubset;
    std::string subsetName;

    PropertyFilter filterObject;
    FilterTracker categoryTracker;
    std::vector<FilterOperation> operations;  // Track filter operations for UI/removal

public:
    SubsetManager();

    // Set the source data to filter from
    void setSourceData(const std::vector<PropertyListing>& data);

    // Filter management
    bool addFilter(FilterCategory category, PropertyFilter::FilterFunction filter, const std::string& description);
    bool removeFilterByCategory(FilterCategory category);
    bool removeFilterByIndex(size_t index);
    void clearFilters();

    // Apply filters to create the subset
    bool applyFilters();

    // Information about filters and results
    size_t getFilterCount() const;
    const std::vector<FilterOperation>& getFilterOperations() const;
    const std::vector<PropertyListing>& getSubset() const;
    void setSubsetName(const std::string& name);
    std::string getSubsetName() const;

    // Check if a category already has a filter
    bool hasCategoryFilter(FilterCategory category) const;
};
