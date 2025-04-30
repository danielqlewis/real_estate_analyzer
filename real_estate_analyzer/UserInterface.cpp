#include "UserInterface.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

UserInterface::UserInterface(std::shared_ptr<ProgramController> controller)
    : controller(controller) {
    // Initialize UI components
    createMainScreen();
}

UserInterface::~UserInterface() {
    // Cleanup if needed
}

void UserInterface::createMainScreen() {
    // This will be implemented with FTXUI components
}

void UserInterface::run() {
    // Create a screen and run the UI loop
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    screen.Loop(mainComponent);
}