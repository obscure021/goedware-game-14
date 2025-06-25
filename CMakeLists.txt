cmake_minimum_required(VERSION 3.28)
project(CMakeSFML3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Let CMake find SFML 3 from system paths (e.g., Homebrew-installed)
find_package(SFML 3 COMPONENTS Window Graphics Audio System REQUIRED)


add_executable(main
    src/main.cpp
    src/classes/Scene.cpp
    src/classes/Object.cpp
    src/classes/objects/PlayerObject.cpp
    src/classes/objects/InteractableObject.cpp
    src/classes/objects/AnimatedSpriteObject.cpp
    src/classes/objects/ConverterObject.cpp
    src/classes/objects/DebugObject.cpp
    src/classes/utils/Helpers.cpp
    src/classes/utils/Structs.hpp
    ${SOURCES}
)


target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/classes
    )

# Link to SFML 3 imported targets
target_link_libraries(main PRIVATE
    SFML::Window
    SFML::Graphics
    SFML::Audio
    SFML::System
)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)