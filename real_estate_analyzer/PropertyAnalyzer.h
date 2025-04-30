#pragma once

#include <vector>
#include <map>
#include <utility>  // for std::pair
#include <functional>
#include "PropertyListing.h"
#include "CustomEnums.h"

class PropertyAnalyzer {
public:

    using MetricFunction = std::function<double(const PropertyListing&)>;

    // Basic statistical functions
    static double calculateMean(const std::vector<double>& values);
    static double calculateMedian(const std::vector<double>& values);
    static double calculateAverage(const std::vector<double>& values, const AverageType avgtyp);

    // Property specific calculations
    static double calculateAveragePrice(const std::vector<PropertyListing>& properties, const AverageType avgtyp);
    static double calculateAveragePricePerSqFt(const std::vector<PropertyListing>& properties, const AverageType avgtyp);
    static double calculateAverageDaysOnMarket(const std::vector<PropertyListing>& properties, const AverageType avgtyp);


    // Helper functions to extract specific data from properties
    static std::vector<double> extractPrices(const std::vector<PropertyListing>& properties);
    static std::vector<double> extractPricesPerSqFt(const std::vector<PropertyListing>& properties);
    static std::vector<double> extractDaysOnMarket(const std::vector<PropertyListing>& properties);

    // Metric selector functions
    static double getPrice(const PropertyListing& listing);
    static double getPricePerSqFt(const PropertyListing& listing);
    static double getDaysOnMarket(const PropertyListing& listing);

    // Will add regression and other functions later
    static std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y);
    static std::pair<double, double> analyzeOverTime(const std::vector<PropertyListing>& properties, MetricFunction metricFn);

    static std::map<PropertyType, int> countPropertiesByType(const std::vector<PropertyListing>& properties);
    static std::map<SaleStatus, int> countBySaleStatus(const std::vector<PropertyListing>& properties);


    struct PropertyAnalysisResult {
        double meanPrice = 0.0;
        double medianPrice = 0.0;
        double meanPricePerSqFt = 0.0;
        double medianPricePerSqFt = 0.0;
        double meanDaysOnMarket = 0.0;
        double medianDaysOnMarket = 0.0;
        std::map<PropertyType, int> countByPropertyType;
        std::map<SaleStatus, int> countBySaleStatus;
        size_t totalProperties = 0;

        // Time-based analysis results (slope, intercept)
        std::pair<double, double> priceTrend;
        std::pair<double, double> pricePerSqFtTrend;
        std::pair<double, double> daysOnMarketTrend;
    };

    // Comprehensive analysis method
    static PropertyAnalysisResult analyzeDataset(const std::vector<PropertyListing>& dataset, bool includeTimeTrends = false);
};