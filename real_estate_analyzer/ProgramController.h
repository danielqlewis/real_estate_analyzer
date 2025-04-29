#pragma once

#include <string>
#include <vector>
#include "PropertyListing.h"
#include "CustomEnums.h"

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

public:
    // Constructor and destructor
    ProgramController();
    ~ProgramController();

    // State management
    ProgramState getCurrentState() const;
    void setState(ProgramState newState);

    // Core flow methods
    bool loadFullDataset(const std::string& filePath);
    bool createFirstSubset();
    bool createSecondSubset();
    void runAnalysis();
    void displayResults();

    // Reset to start over
    void reset();
};
