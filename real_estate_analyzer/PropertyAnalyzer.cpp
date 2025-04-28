#include "PropertyAnalyzer.h"
#include "CustomEnums.h"
#include <numeric>      // For std::accumulate
#include <algorithm>    // For std::sort
#include <cmath>        // For mathematical functions

// Calculate mean of a vector of values
double PropertyAnalyzer::calculateMean(const std::vector<double>& values) {
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

// Calculate median of a vector of values
double PropertyAnalyzer::calculateMedian(const std::vector<double>& values) {
    // Create a copy of the vector since we need to sort it
    std::vector<double> sorted = values;
    std::sort(sorted.begin(), sorted.end());

    size_t size = sorted.size();
    if (size % 2 == 0) {
        // Even number of elements - average the middle two
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }
    else {
        // Odd number of elements - return the middle one
        return sorted[size / 2];
    }
}

//Calculate average of a vector of values
double PropertyAnalyzer::calculateAverage(const std::vector<double>& values, const AverageType avgtyp) {
    if (values.empty()) {
        return 0.0;
    }

    if (avgtyp == AverageType::Mean) {
        return calculateMean(values);
    }
    else {
        return calculateMedian(values);
    }
}

// Extract prices from properties
std::vector<double> PropertyAnalyzer::extractPrices(const std::vector<PropertyListing>& properties) {
    std::vector<double> prices;
    prices.reserve(properties.size());

    for (const auto& property : properties) {
        prices.push_back(static_cast<double>(property.getPrice()));
    }

    return prices;
}


// Extract price per square foot from properties
std::vector<double> PropertyAnalyzer::extractPricesPerSqFt(const std::vector<PropertyListing>& properties) {
    std::vector<double> prices;
    prices.reserve(properties.size());

    for (const auto& property : properties) {
        prices.push_back(static_cast<double>(property.pricePerSqFt()));
    }

    return prices;
}

// Calculate average price
double PropertyAnalyzer::calculateAveragePrice(const std::vector<PropertyListing>& properties, const AverageType avgtyp) {
    return calculateAverage(extractPrices(properties), avgtyp);
}

// Calculate average price per square foot
double PropertyAnalyzer::calculateAveragePricePerSqFt(const std::vector<PropertyListing>& properties, const AverageType avgtyp) {
    return calculateAverage(extractPricesPerSqFt(properties), avgtyp);
}