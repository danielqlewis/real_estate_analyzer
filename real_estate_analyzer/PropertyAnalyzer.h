#pragma once

#include <vector>
#include <map>
#include <utility>  // for std::pair
#include "PropertyListing.h"
#include "CustomEnums.h"

class PropertyAnalyzer {
public:
    // Basic statistical functions
    static double calculateMean(const std::vector<double>& values);
    static double calculateMedian(const std::vector<double>& values);
    static double calculateAverage(const std::vector<double>& values, const AverageType avgtyp);

    // Property specific calculations
    static double calculateAveragePrice(const std::vector<PropertyListing>& properties, const AverageType avgtyp);
    static double calculateAveragePricePerSqFt(const std::vector<PropertyListing>& properties, const AverageType avgtyp);


    // Helper functions to extract specific data from properties
    static std::vector<double> extractPrices(const std::vector<PropertyListing>& properties);
    static std::vector<double> extractPricesPerSqFt(const std::vector<PropertyListing>& properties);

    // Will add regression and other functions later
};