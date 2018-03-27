#
#  Build MIPSimu
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT


# Tells CMake to run moc automatically
set(CMAKE_AUTOMOC ON)

# Import Qt5
find_package(Qt5Widgets)


# Source files
set(SOURCES

    "src/app/system.h"
    "src/app/system.cc"
    "src/app/sysworker.h"
    "src/app/sysworker.cc"
    "src/app/memoryloader.h"
    "src/app/memoryloader.cc"
    "src/app/screen.h"
    "src/app/screen.cc"
    "src/app/keyboard.h"
    "src/app/keyboard.cc"

    "mainwindow.h"
    "mainwindow.cc"
)


# Create the library
add_library(mipsimu-native ${SOURCES})
target_link_libraries(mipsimu-native Qt5::Widgets)
