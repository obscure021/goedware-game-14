cmake_minimum_required(VERSION 3.28)
project(CMakeSFML3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Let CMake find SFML 3 from system paths (e.g., Homebrew-installed)
find_package(SFML 3 COMPONENTS Window Graphics Audio System REQUIRED)

add_executable(main main.cpp)

# Link to SFML 3 imported targets
target_link_libraries(main PRIVATE
    SFML::Window
    SFML::Graphics
    SFML::Audio
    SFML::System
)
