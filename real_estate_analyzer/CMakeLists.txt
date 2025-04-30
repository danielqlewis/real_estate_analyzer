cmake_minimum_required(VERSION 3.11)
project(real_estate_analyzer VERSION 0.1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FTXUI
include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG v3.0.0
)
FetchContent_MakeAvailable(ftxui)

# Add project source files
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

# Create executable
add_executable(real_estate_analyzer ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(real_estate_analyzer
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)