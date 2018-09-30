#
#  Build MIPSimu - native app
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT


# Tells CMake to run moc automatically
set(CMAKE_AUTOMOC ON)

# Import Qt5
find_package(Qt5Widgets)


# Source files
set(SOURCES
    "system/system.h"
    "system/system.cc"
    "system/sysworker.h"
    "system/sysworker.cc"
    "system/memoryloader.h"
    "system/memoryloader.cc"
    "external/screen.h"
    "external/screen.cc"
    "external/keyboard.h"
    "external/keyboard.cc"

    "mainwindow.h"
    "mainwindow.cc"
)

# Include this directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Create the library
add_library(mipsimu-native ${SOURCES})
target_link_libraries(mipsimu-native Qt5::Widgets)
