#include "SubsetManager.h"
#include <iostream>

SubsetManager::SubsetManager() {
    // Initialize if needed
}

void SubsetManager::setSourceData(const std::vector<PropertyListing>& data) {
    sourceData = data;
}

bool SubsetManager::addFilter(FilterCategory category, PropertyFilter::FilterFunction filter, const std::string& description) {
    // Check if category already has a filter
    if (hasCategoryFilter(category)) {
        std::cerr << "A filter for this category already exists. Please remove it first." << std::endl;
        return false;
    }

    // Test if filter would exclude all properties
    PropertyFilter testFilter;
    testFilter.addFilter(filter);
    std::vector<PropertyListing> testResult = testFilter.apply(sourceData);

    if (testResult.empty()) {
        std::cerr << "Warning: This filter would exclude all properties." << std::endl;
        return false;
    }

    // Add the filter
    filterObject.addFilter(filter);

    // Update the tracker
    switch (category) {
    case FilterCategory::SaleStatus: categoryTracker.saleStatus = true; break;
    case FilterCategory::PropertyType: categoryTracker.propertyType = true; break;
    case FilterCategory::Location: categoryTracker.location = true; break;
    case FilterCategory::BedBaths: categoryTracker.bedBaths = true; break;
    case FilterCategory::Size: categoryTracker.size = true; break;
    case FilterCategory::LotSize: categoryTracker.lotSize = true; break;
    case FilterCategory::ListingDate: categoryTracker.listingDate = true; break;
    case FilterCategory::Price: categoryTracker.price = true; break;
    case FilterCategory::DaysOnMarket: categoryTracker.daysOnMarket = true; break;
    case FilterCategory::YearBuilt: categoryTracker.yearBuilt = true; break;
    }

    // Record the operation
    FilterOperation op;
    op.category = category;
    op.filterIndex = filterObject.getFilterCount() - 1;
    op.description = description;
    operations.push_back(op);

    return true;
}

bool SubsetManager::removeFilterByCategory(FilterCategory category) {
    // Find the operation for this category
    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i].category == category) {
            // Remove this filter
            if (!filterObject.removeFilterByIndex(operations[i].filterIndex)) {
                return false;
            }

            // Update the tracker
            switch (category) {
            case FilterCategory::SaleStatus: categoryTracker.saleStatus = false; break;
            case FilterCategory::PropertyType: categoryTracker.propertyType = false; break;
            case FilterCategory::Location: categoryTracker.location = false; break;
            case FilterCategory::BedBaths: categoryTracker.bedBaths = false; break;
            case FilterCategory::Size: categoryTracker.size = false; break;
            case FilterCategory::LotSize: categoryTracker.lotSize = false; break;
            case FilterCategory::ListingDate: categoryTracker.listingDate = false; break;
            case FilterCategory::Price: categoryTracker.price = false; break;
            case FilterCategory::DaysOnMarket: categoryTracker.daysOnMarket = false; break;
            case FilterCategory::YearBuilt: categoryTracker.yearBuilt = false; break;
            }

            // Remove the operation
            operations.erase(operations.begin() + i);

            // Need to rebuild filter indices since we've removed one
            for (size_t j = i; j < operations.size(); ++j) {
                operations[j].filterIndex--;
            }

            return true;
        }
    }

    return false;  // Category not found
}

bool SubsetManager::removeFilterByIndex(size_t index) {
    if (index >= operations.size()) {
        return false;
    }

    FilterCategory category = operations[index].category;
    return removeFilterByCategory(category);
}

void SubsetManager::clearFilters() {
    filterObject.clearFilters();
    operations.clear();
    categoryTracker = FilterTracker();  // Reset all to false
}

bool SubsetManager::applyFilters() {
    resultSubset = filterObject.apply(sourceData);

    if (resultSubset.empty()) {
        std::cerr << "Warning: No properties match the selected filters." << std::endl;
        return false;
    }

    std::cout << "Created subset with " << resultSubset.size() << " properties." << std::endl;
    return true;
}

size_t SubsetManager::getFilterCount() const {
    return operations.size();
}

const std::vector<FilterOperation>& SubsetManager::getFilterOperations() const {
    return operations;
}

const std::vector<PropertyListing>& SubsetManager::getSubset() const {
    return resultSubset;
}

void SubsetManager::setSubsetName(const std::string& name) {
    subsetName = name;
}

std::string SubsetManager::getSubsetName() const {
    return subsetName;
}

bool SubsetManager::hasCategoryFilter(FilterCategory category) const {
    switch (category) {
    case FilterCategory::SaleStatus: return categoryTracker.saleStatus;
    case FilterCategory::PropertyType: return categoryTracker.propertyType;
    case FilterCategory::Location: return categoryTracker.location;
    case FilterCategory::BedBaths: return categoryTracker.bedBaths;
    case FilterCategory::Size: return categoryTracker.size;
    case FilterCategory::LotSize: return categoryTracker.lotSize;
    case FilterCategory::ListingDate: return categoryTracker.listingDate;
    case FilterCategory::Price: return categoryTracker.price;
    case FilterCategory::DaysOnMarket: return categoryTracker.daysOnMarket;
    case FilterCategory::YearBuilt: return categoryTracker.yearBuilt;
    }
    return false;  // Should never reach here
}