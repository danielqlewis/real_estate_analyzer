#include "PropertyFilter.h"
#include <algorithm>

void PropertyFilter::addFilter(FilterFunction filter) {
    filters.push_back(filter);
}

std::vector<PropertyListing> PropertyFilter::apply(const std::vector<PropertyListing>& properties) const {
    if (filters.empty()) {
        return properties; // No filters, return all properties
    }

    std::vector<PropertyListing> result;

    for (const auto& property : properties) {
        bool passesAllFilters = true;

        for (const auto& filter : filters) {
            if (!filter(property)) {
                passesAllFilters = false;
                break;
            }
        }

        if (passesAllFilters) {
            result.push_back(property);
        }
    }

    return result;
}

void PropertyFilter::clearFilters() {
    filters.clear();
}

// Implementation of factory methods

// --- Sale Status ---
PropertyFilter::FilterFunction PropertyFilter::hasSaleStatus(SaleStatus status) {
    return [status](const PropertyListing& property) {
        return property.getSaleStatus() == status;
    };
}


// --- Property Type ---
PropertyFilter::FilterFunction PropertyFilter::hasPropertyType(PropertyType type) {
    return [type](const PropertyListing& property) {
        return property.getPropertyType() == type;
    };
}


// --- Location ---
PropertyFilter::FilterFunction PropertyFilter::inTown(const std::string& townName) {
    return [townName](const PropertyListing& property) {
        return property.getTownName() == townName;
    };
}

PropertyFilter::FilterFunction PropertyFilter::inState(const std::string& state) {
    return [state](const PropertyListing& property) {
        return property.getState() == state;
    };
}

PropertyFilter::FilterFunction PropertyFilter::inZipcode(const std::string& zipcode) {
    return [zipcode](const PropertyListing& property) {
        return property.getZipcode() == zipcode;
    };
}

// --- Beds / Baths ---
PropertyFilter::FilterFunction PropertyFilter::bedroomsAtLeast(int num) {
    return [num](const PropertyListing& property) {
        return property.getNumberOfBed() >= num;
    };
}

PropertyFilter::FilterFunction PropertyFilter::bedroomsAtMost(int num) {
    return [num](const PropertyListing& property) {
        return property.getNumberOfBed() <= num;
    };
}

PropertyFilter::FilterFunction PropertyFilter::bathroomsAtLeast(int num) {
    return [num](const PropertyListing& property) {
        return property.getNumberOfBath() >= num;
    };
}

PropertyFilter::FilterFunction PropertyFilter::bathroomsAtMost(int num) {
    return [num](const PropertyListing& property) {
        return property.getNumberOfBath() <= num;
    };
}


// --- Size ---
PropertyFilter::FilterFunction PropertyFilter::minSize(int minSize) {
    return [minSize](const PropertyListing& property) {
        return property.getSize() >= minSize;
    };
}

PropertyFilter::FilterFunction PropertyFilter::maxSize(int maxSize) {
    return [maxSize](const PropertyListing& property) {
        return property.getSize() <= maxSize;
    };
}

// --- Lot Size ---
PropertyFilter::FilterFunction PropertyFilter::minLotSize(int minSize) {
    return [minSize](const PropertyListing& property) {
        return property.getLotSize() >= minSize;
    };
}

PropertyFilter::FilterFunction PropertyFilter::maxLotSize(int maxSize) {
    return [maxSize](const PropertyListing& property) {
        return property.getLotSize() <= maxSize;
    };
}


// --- Listing Date ---
PropertyFilter::FilterFunction PropertyFilter::listedAfter(const std::chrono::year_month_day& date) {
    return [date](const PropertyListing& property) {
        return property.getListingDate() > date;
    };
}

PropertyFilter::FilterFunction PropertyFilter::listedBefore(const std::chrono::year_month_day& date) {
    return [date](const PropertyListing& property) {
        return property.getListingDate() < date;
    };
}

PropertyFilter::FilterFunction PropertyFilter::listedBetween(
    const std::chrono::year_month_day& startDate,
    const std::chrono::year_month_day& endDate) {
    return [startDate, endDate](const PropertyListing& property) {
        auto date = property.getListingDate();
        return date >= startDate && date <= endDate;
    };
}


// --- Price ---
PropertyFilter::FilterFunction PropertyFilter::maxPrice(int maxPrice) {
    return [maxPrice](const PropertyListing& property) {
        return property.getPrice() <= maxPrice;
    };
}

PropertyFilter::FilterFunction PropertyFilter::minPrice(int minPrice) {
    return [minPrice](const PropertyListing& property) {
        return property.getPrice() >= minPrice;
    };
}

PropertyFilter::FilterFunction PropertyFilter::priceBetween(int minPrice, int maxPrice) {
    return [minPrice, maxPrice](const PropertyListing& property) {
        int price = property.getPrice();
        return price >= minPrice && price <= maxPrice;
    };
}


// --- Days on Market ---
PropertyFilter::FilterFunction PropertyFilter::minDaysOnMarket(int days) {
    return [days](const PropertyListing& property) {
        return property.getDaysOnMarket() >= days;
    };
}

PropertyFilter::FilterFunction PropertyFilter::maxDaysOnMarket(int days) {
    return [days](const PropertyListing& property) {
        return property.getDaysOnMarket() <= days;
    };
}


// --- Year Built ---
PropertyFilter::FilterFunction PropertyFilter::minYearBuilt(int minYear) {
    return [minYear](const PropertyListing& property) {
        int year = property.getYearBuilt();
        return year >= minYear;
    };
}


PropertyFilter::FilterFunction PropertyFilter::maxYearBuilt(int maxYear) {
    return [maxYear](const PropertyListing& property) {
        int year = property.getYearBuilt();
        return year <= maxYear;
    };
}


PropertyFilter::FilterFunction PropertyFilter::yearBuiltBetween(int minYear, int maxYear) {
    return [minYear, maxYear](const PropertyListing& property) {
        int year = property.getYearBuilt();
        return year >= minYear && year <= maxYear;
    };
}








