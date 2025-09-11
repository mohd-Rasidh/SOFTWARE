cmake_minimum_required(VERSION 3.16)

project(DATA_WIPER VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Add ALL your source and header files here
set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    diskmanager.h
    diskmanager.cpp
    certificategenerator.h
    certificategenerator.cpp
)

# This command creates the executable and includes all the files
add_executable(DATA_WIPER ${PROJECT_SOURCES})

# This command links the necessary Qt library
target_link_libraries(DATA_WIPER PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set properties for Windows/Mac deployment
set_target_properties(DATA_WIPER PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
