#pragma once

#include <string>
#include <memory>
#include "ProgramController.h"

// Forward declarations for FTXUI components
namespace ftxui {
    class Component;
    class Screen;
}

class UserInterface {
private:
    std::shared_ptr<ProgramController> controller;

    // FTXUI specific members
    std::shared_ptr<ftxui::Component> mainComponent;

    // UI state and helper methods (to be implemented)
    void createMainScreen();
    void createDataSelectionScreen();
    void createFirstSubsetScreen();
    void createSecondSubsetScreen();
    void createAnalysisScreen();
    void createResultsScreen();

public:
    UserInterface(std::shared_ptr<ProgramController> controller);
    ~UserInterface();

    // Start the UI
    void run();
};
