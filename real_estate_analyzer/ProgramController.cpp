#include "ProgramController.h"
#include "CsvReader.h"
#include <iostream>

// Constructor
ProgramController::ProgramController() : currentState(ProgramState::SelectingFullDataset) {
    firstSubsetManager.setSubsetName("First Subset");
    secondSubsetManager.setSubsetName("Second Subset");
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

        // Set source data for subset managers
        firstSubsetManager.setSourceData(fullDataset);
        secondSubsetManager.setSourceData(fullDataset);

        // Move to the next state
        setState(ProgramState::SelectingFirstSubset);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading dataset: " << e.what() << std::endl;
        return false;
    }
}


bool ProgramController::createFirstSubset() {
    bool result = firstSubsetManager.applyFilters();
    if (result) {
        setState(ProgramState::SelectingSecondSubset);
    }
    return result;
}


bool ProgramController::createSecondSubset() {
    bool result = secondSubsetManager.applyFilters();
    if (result) {
        setState(ProgramState::RunningAnalysis);
    }
    return result;
}

void ProgramController::runAnalysis() {
    // Check if we have valid datasets to analyze
    if (fullDataset.empty()) {
        std::cerr << "Error: Cannot run analysis. No full dataset loaded." << std::endl;
        return;
    }

    const std::vector<PropertyListing>& firstSubset = firstSubsetManager.getSubset();
    const std::vector<PropertyListing>& secondSubset = secondSubsetManager.getSubset();

    if (firstSubset.empty() || secondSubset.empty()) {
        std::cerr << "Error: Cannot run analysis. Both subsets must be created." << std::endl;
        return;
    }

    // Create analysis results for each dataset
    analysisResults.fullDatasetResults = PropertyAnalyzer::analyzeDataset(fullDataset, false);
    analysisResults.firstSubsetResults = PropertyAnalyzer::analyzeDataset(firstSubset, true);
    analysisResults.secondSubsetResults = PropertyAnalyzer::analyzeDataset(secondSubset, true);

    // Set labels for the results
    analysisResults.fullDatasetName = "Full Dataset";
    analysisResults.firstSubsetName = firstSubsetManager.getSubsetName();
    analysisResults.secondSubsetName = secondSubsetManager.getSubsetName();

    // Analysis is complete, move to display results
    setState(ProgramState::DisplayingResults);
    std::cout << "Analysis complete. Ready to display results." << std::endl;
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