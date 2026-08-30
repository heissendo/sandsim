cmake_minimum_required(VERSION 3.25)

# Project name and C++ standard
project(pingpong)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Enable Qt's Meta-Object Compiler (MOC) and other tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find packages package
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Collect source and header files
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h")

# Define the executable target
add_executable(pingpong
    ${SRC_FILES}
    ${HEADER_FILES}
)
# Add include directories for headers and generated files
target_include_directories(pingpong
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/header    # Include project headers
    ${CMAKE_BINARY_DIR}                   
)

# Link libraries 
target_link_libraries(pingpong PRIVATE Qt6::Widgets)

# Set the output directory for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
