#include <memory>
#include "ProgramController.h"
#include "UserInterface.h"

int main() {
    // Create the controller
    auto controller = std::make_shared<ProgramController>();

    // Create and run the UI
    UserInterface ui(controller);
    ui.run();

    return 0;
}