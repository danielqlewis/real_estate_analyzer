#pragma once

#include <string>
#include <vector>
#include "PropertyListing.h"
#include "PropertyFilter.h"
#include "PropertyAnalyzer.h"
#include "SubsetManager.h"
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

struct ComparativeAnalysis {
    std::string fullDatasetName;
    std::string firstSubsetName;
    std::string secondSubsetName;
    PropertyAnalyzer::PropertyAnalysisResult fullDatasetResults;
    PropertyAnalyzer::PropertyAnalysisResult firstSubsetResults;
    PropertyAnalyzer::PropertyAnalysisResult secondSubsetResults;
};


class ProgramController {
private:
    // Current state of the program
    ProgramState currentState;

    // Data collections
    std::vector<PropertyListing> fullDataset;
    std::vector<PropertyListing> firstSubset;
    std::vector<PropertyListing> secondSubset;

    // Tracking information about the datasets
    std::string fullDatasetPath;
    std::string firstSubsetName;
    std::string secondSubsetName;

    PropertyFilter firstSubsetFilter;
    PropertyFilter secondSubsetFilter;

    SubsetManager firstSubsetManager;
    SubsetManager secondSubsetManager;

    
    void clearSubsetFilters(int subsetIndex);
    size_t getSubsetFilterCount(int subsetIndex) const;
    bool applySubsetFilters(int subsetIndex);

    FilterTracker firstSubsetFilterTracker;
    FilterTracker secondSubsetFilterTracker;

    ComparativeAnalysis analysisResults;





public:
    // Constructor and destructor
    ProgramController();
    ~ProgramController();

    // State management
    ProgramState getCurrentState() const;
    void setState(ProgramState newState);

    // Core flow methods
    bool loadFullDataset(const std::string& filePath);
    bool addFilterToSubset(int subsetIndex, FilterCategory category, PropertyFilter::FilterFunction filter);
    bool createFirstSubset();
    bool createSecondSubset();
    void runAnalysis();
    void displayResults();

    // Reset to start over
    void reset();


    const ComparativeAnalysis& getAnalysisResults() const { return analysisResults; }
};
