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

// Create the first subset (placeholder implementation)
bool ProgramController::createFirstSubset() {
    // This will be implemented later with filtering logic
    std::cout << "First subset created (placeholder)" << std::endl;
    setState(ProgramState::SelectingSecondSubset);
    return true;
}

// Create the second subset (placeholder implementation)
bool ProgramController::createSecondSubset() {
    // This will be implemented later with filtering logic
    std::cout << "Second subset created (placeholder)" << std::endl;
    setState(ProgramState::RunningAnalysis);
    return true;
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