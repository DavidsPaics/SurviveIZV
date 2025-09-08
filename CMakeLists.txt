cmake_minimum_required(VERSION 3.28)
project(SurviveIZV LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(main ${SOURCES})

target_include_directories(main
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

# Create a custom target to copy assets if they change
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMENT "Copying updated assets to output directory"
)

# Make sure the executable depends on the asset copy step
add_dependencies(main copy_assets)