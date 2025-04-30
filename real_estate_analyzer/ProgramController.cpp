#include "ProgramController.h"
#include "CsvReader.h"
#include <iostream>

// Constructor
ProgramController::ProgramController() : currentState(ProgramState::SelectingFullDataset) {
    // Initialize with the first state
}

// Destructor
ProgramController::~ProgramController() {
    // Clean up if needed
}

// Get the current program state
ProgramState ProgramController::getCurrentState() const {
    return currentState;
}

// Set the program state
void ProgramController::setState(ProgramState newState) {
    currentState = newState;
}

// Load full dataset from file
bool ProgramController::loadFullDataset(const std::string& filePath) {
    try {
        fullDatasetPath = filePath;
        fullDataset = CsvReader::readPropertiesFromFile(filePath);

        if (fullDataset.empty()) {
            std::cerr << "No properties found in the file." << std::endl;
            return false;
        }

        std::cout << "Loaded " << fullDataset.size() << " properties from " << filePath << std::endl;

        // Move to the next state
        setState(ProgramState::SelectingFirstSubset);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading dataset: " << e.what() << std::endl;
        return false;
    }
}

bool ProgramController::addFilterToSubset(int subsetIndex, FilterCategory category, PropertyFilter::FilterFunction filter) {
    // Validate subset index
    if (subsetIndex != 0 && subsetIndex != 1) {
        std::cerr << "Error: Invalid subset index. Must be 0 (first subset) or 1 (second subset)." << std::endl;
        return false;
    }

    // Get references to the correct filter and tracker
    PropertyFilter& targetFilter = (subsetIndex == 0) ? firstSubsetFilter : secondSubsetFilter;
    FilterTracker& tracker = (subsetIndex == 0) ? firstSubsetFilterTracker : secondSubsetFilterTracker;

    // Check if category already has a filter
    bool categoryHasFilter = false;

    switch (category) {
    case FilterCategory::SaleStatus:
        categoryHasFilter = tracker.saleStatus;
        break;
    case FilterCategory::PropertyType:
        categoryHasFilter = tracker.propertyType;
        break;
    case FilterCategory::Location:
        categoryHasFilter = tracker.location;
        break;
    case FilterCategory::BedBaths:
        categoryHasFilter = tracker.bedBaths;
        break;
    case FilterCategory::Size:
        categoryHasFilter = tracker.size;
        break;
    case FilterCategory::LotSize:
        categoryHasFilter = tracker.lotSize;
        break;
    case FilterCategory::ListingDate:
        categoryHasFilter = tracker.listingDate;
        break;
    case FilterCategory::Price:
        categoryHasFilter = tracker.price;
        break;
    case FilterCategory::DaysOnMarket:
        categoryHasFilter = tracker.daysOnMarket;
        break;
    case FilterCategory::YearBuilt:
        categoryHasFilter = tracker.yearBuilt;
        break;
    }

    if (categoryHasFilter) {
        std::cerr << "A filter for this category already exists. Please remove it first." << std::endl;
        return false;
    }

    // Check if filter would exclude all properties
    PropertyFilter testFilter;
    testFilter.addFilter(filter);
    std::vector<PropertyListing> testResult = testFilter.apply(fullDataset);

    if (testResult.empty()) {
        std::cerr << "Warning: This filter would exclude all properties." << std::endl;
        return false;
    }

    // Add the filter and mark category as used
    targetFilter.addFilter(filter);

    switch (category) {
    case FilterCategory::SaleStatus:
        tracker.saleStatus = true;
        break;
    case FilterCategory::PropertyType:
        tracker.propertyType = true;
        break;
    case FilterCategory::Location:
        tracker.location = true;
        break;
    case FilterCategory::BedBaths:
        tracker.bedBaths = true;
        break;
    case FilterCategory::Size:
        tracker.size = true;
        break;
    case FilterCategory::LotSize:
        tracker.lotSize = true;
        break;
    case FilterCategory::ListingDate:
        tracker.listingDate = true;
        break;
    case FilterCategory::Price:
        tracker.price = true;
        break;
    case FilterCategory::DaysOnMarket:
        tracker.daysOnMarket = true;
        break;
    case FilterCategory::YearBuilt:
        tracker.yearBuilt = true;
        break;
    }

    return true;
}

void ProgramController::clearSubsetFilters(int subsetIndex) {
    if (subsetIndex == 0) {
        firstSubsetFilter.clearFilters();
        firstSubsetFilterTracker = FilterTracker();
    }
    else if (subsetIndex == 1) {
        secondSubsetFilter.clearFilters();
        secondSubsetFilterTracker = FilterTracker();
    }
    else {
        std::cerr << "Error: Invalid subset index." << std::endl;
    }
}

size_t ProgramController::getSubsetFilterCount(int subsetIndex) const {
    if (subsetIndex == 0) {
        return firstSubsetFilter.getFilterCount();
    }
    else if (subsetIndex == 1) {
        return secondSubsetFilter.getFilterCount();
    }
    return 0; // Invalid index
}

bool ProgramController::applySubsetFilters(int subsetIndex) {
    if (subsetIndex != 0 && subsetIndex != 1) {
        std::cerr << "Error: Invalid subset index." << std::endl;
        return false;
    }

    std::vector<PropertyListing>& targetSubset = (subsetIndex == 0) ? firstSubset : secondSubset;
    std::string& targetName = (subsetIndex == 0) ? firstSubsetName : secondSubsetName;
    PropertyFilter& targetFilter = (subsetIndex == 0) ? firstSubsetFilter : secondSubsetFilter;

    targetSubset = targetFilter.apply(fullDataset);
    targetName = "Custom filtered subset"; // This could be enhanced later

    if (targetSubset.empty()) {
        std::cerr << "Warning: No properties match the selected filters." << std::endl;
        return false;
    }

    std::cout << "Created subset with " << targetSubset.size() << " properties." << std::endl;

    // Update program state if appropriate
    if (subsetIndex == 0 && currentState == ProgramState::SelectingFirstSubset) {
        setState(ProgramState::SelectingSecondSubset);
    }
    else if (subsetIndex == 1 && currentState == ProgramState::SelectingSecondSubset) {
        setState(ProgramState::RunningAnalysis);
    }

    return true;
}


bool ProgramController::createFirstSubset() {
    return applySubsetFilters(0);
}

bool ProgramController::createSecondSubset() {
    return applySubsetFilters(1);
}

// Run analysis (placeholder implementation)
void ProgramController::runAnalysis() {
    // This will be implemented later with your PropertyAnalyzer
    std::cout << "Analysis run (placeholder)" << std::endl;
    setState(ProgramState::DisplayingResults);
}

// Display results (placeholder implementation)
void ProgramController::displayResults() {
    // This will be implemented with your UI logic
    std::cout << "Results displayed (placeholder)" << std::endl;
}

// Reset to start over
void ProgramController::reset() {
    // Clear all data
    fullDataset.clear();
    firstSubset.clear();
    secondSubset.clear();

    // Reset strings
    fullDatasetPath = "";
    firstSubsetName = "";
    secondSubsetName = "";

    // Reset state
    setState(ProgramState::SelectingFullDataset);

    std::cout << "Program reset. Ready to start over." << std::endl;
}