cmake_minimum_required(VERSION 3.25)

project(sandsim LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt's Meta-Object Compiler, for Q_OBJECT in MainWindow
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(sandsim
    src/main.cpp
    src/mainwindow.cpp
    src/particle.cpp
    src/grid.cpp
    header/mainwindow.h
    header/particle.h
    header/grid.h
    header/coordinates.h
)

target_compile_features(sandsim PRIVATE cxx_std_23)

target_include_directories(sandsim PRIVATE header)

target_link_libraries(sandsim PRIVATE Qt6::Widgets)
