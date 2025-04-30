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


// Extract days on market from properties
std::vector<double> PropertyAnalyzer::extractDaysOnMarket(const std::vector<PropertyListing>& properties) {
    std::vector<double> days;
    days.reserve(properties.size());

    for (const auto& property : properties) {
        days.push_back(static_cast<double>(property.getDaysOnMarket()));
    }

    return days;
}

// Calculate average price
double PropertyAnalyzer::calculateAveragePrice(const std::vector<PropertyListing>& properties, const AverageType avgtyp) {
    return calculateAverage(extractPrices(properties), avgtyp);
}

// Calculate average price per square foot
double PropertyAnalyzer::calculateAveragePricePerSqFt(const std::vector<PropertyListing>& properties, const AverageType avgtyp) {
    return calculateAverage(extractPricesPerSqFt(properties), avgtyp);
}


// Calculate average days on market
double PropertyAnalyzer::calculateAverageDaysOnMarket(const std::vector<PropertyListing>& properties, const AverageType avgtyp) {
    return calculateAverage(extractDaysOnMarket(properties), avgtyp);
}


std::pair<double, double> PropertyAnalyzer::linearRegression(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.empty() || y.empty() || x.size() != y.size()) {
        // Handle error case - return zeroes or throw an exception
        return std::make_pair(0.0, 0.0);
    }

    int n = x.size();
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);

    double sum_xx = 0.0;
    for (const auto& value : x) {
        sum_xx += std::pow(value, 2);
    }

    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

    double denominator = (n * sum_xx) - std::pow(sum_x, 2);
    if (denominator == 0.0) {
        // If denominator is zero, slope is undefined (vertical line)
        // Return slope = 0 and intercept = average of y
        return std::make_pair(0.0, sum_y / n);
    }

    double m = ((n * sum_xy) - (sum_x * sum_y)) / denominator;
    double b = ((sum_y * sum_xx) - (sum_x * sum_xy)) / denominator;

    return std::make_pair(m, b);
}


// Metric selector functions
double PropertyAnalyzer::getPrice(const PropertyListing& listing) {
    return static_cast<double>(listing.getPrice());
}

double PropertyAnalyzer::getPricePerSqFt(const PropertyListing& listing) {
    return listing.pricePerSqFt();
}

double PropertyAnalyzer::getDaysOnMarket(const PropertyListing& listing) {
    return static_cast<double>(listing.getDaysOnMarket());
}

// Wrapper for analyzing metrics over time
std::pair<double, double> PropertyAnalyzer::analyzeOverTime(
    const std::vector<PropertyListing>& properties,
    MetricFunction metricFn) {

    if (properties.size() < 2) {
        return std::make_pair(0.0, 0.0); // Not enough data points
    }

    // Create a copy of properties so we can sort by date
    std::vector<PropertyListing> sortedProperties = properties;

    // Sort by listing date
    std::sort(sortedProperties.begin(), sortedProperties.end(),
        [](const PropertyListing& a, const PropertyListing& b) {
            return a.getListingDate() < b.getListingDate();
        });

    // Get the earliest date
    auto day0 = sortedProperties[0].getListingDate();

    // Extract x values (days since earliest date)
    std::vector<double> x;
    x.reserve(sortedProperties.size());

    // Extract y values (metric values)
    std::vector<double> y;
    y.reserve(sortedProperties.size());

    for (const auto& property : sortedProperties) {
        // Calculate days between dates
        auto daysSinceStart = std::chrono::sys_days(property.getListingDate()) -
            std::chrono::sys_days(day0);

        x.push_back(static_cast<double>(daysSinceStart.count()));
        y.push_back(metricFn(property));
    }

    // Calculate linear regression
    return linearRegression(x, y);
}

std::map<PropertyType, int> PropertyAnalyzer::countPropertiesByType(const std::vector<PropertyListing>& properties) {
    std::map<PropertyType, int> counts;

    // Initialize counts for all property types to zero
    counts[PropertyType::SingleFamily] = 0;
    counts[PropertyType::Condo] = 0;
    counts[PropertyType::Apartment] = 0;

    // Count properties of each type
    for (const auto& property : properties) {
        counts[property.getPropertyType()]++;
    }

    return counts;
}

std::map<SaleStatus, int> PropertyAnalyzer::countBySaleStatus(const std::vector<PropertyListing>& properties) {
    std::map<SaleStatus, int> counts;

    // Initialize counts for all sale statuses to zero
    counts[SaleStatus::Active] = 0;
    counts[SaleStatus::Sold] = 0;
    counts[SaleStatus::Pending] = 0;

    // Count properties of each status
    for (const auto& property : properties) {
        counts[property.getSaleStatus()]++;
    }

    return counts;
}

PropertyAnalyzer::PropertyAnalysisResult PropertyAnalyzer::analyzeDataset(
    const std::vector<PropertyListing>& dataset,
    bool includeTimeTrends
) {
    PropertyAnalysisResult result;

    // Calculate basic statistics
    result.totalProperties = dataset.size();

    // Calculate price statistics
    result.meanPrice = calculateAveragePrice(dataset, AverageType::Mean);
    result.medianPrice = calculateAveragePrice(dataset, AverageType::Median);

    // Calculate price per square foot statistics
    result.meanPricePerSqFt = calculateAveragePricePerSqFt(dataset, AverageType::Mean);
    result.medianPricePerSqFt = calculateAveragePricePerSqFt(dataset, AverageType::Median);

    // Calculate days on market statistics
    result.meanDaysOnMarket = calculateAverageDaysOnMarket(dataset, AverageType::Mean);
    result.medianDaysOnMarket = calculateAverageDaysOnMarket(dataset, AverageType::Median);

    // Calculate property type distribution
    result.countByPropertyType = countPropertiesByType(dataset);

    // Calculate sale status distribution
    result.countBySaleStatus = countBySaleStatus(dataset);

    // For time-based analysis
    if (includeTimeTrends && dataset.size() >= 2) {
        // Analyze price trend over time
        result.priceTrend = analyzeOverTime(dataset, getPrice);

        // Analyze price per square foot trend over time
        result.pricePerSqFtTrend = analyzeOverTime(dataset, getPricePerSqFt);

        // Analyze days on market trend over time
        result.daysOnMarketTrend = analyzeOverTime(dataset, getDaysOnMarket);
    }

    return result;
}