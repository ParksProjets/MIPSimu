#
#  Build MIPSimu
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT

cmake_minimum_required(VERSION 3.3)
project(mipsimu)


# Unit tests
option(MIPSIMU_ENABLE_TESTS "Enable MIPSimu unit tests." OFF)
if(MIPSIMU_ENABLE_TESTS)
    add_subdirectory(unittests)
endif()

# Build the native version
option(MIPSIMU_BUILD_NATIVE "Build MIPSimu native or JS version?" ON)


# Include source directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Tells CMake to run moc automatically
set(CMAKE_AUTOMOC ON)

# Import Qt5
find_package(Qt5Widgets)


# Source files
set(SOURCES
    "src/core/bus.h"
    "src/core/bus.cc"
    "src/core/disassembler.h"
    "src/core/disassembler.cc"
    "src/core/processor.h"
    "src/core/processor.cc"

    "src/peripherals/ram.h"
    "src/peripherals/ram.cc"
    "src/peripherals/timer.h"
    "src/peripherals/timer.cc"
    "src/peripherals/external.h"
    "src/peripherals/external.cc"
    "src/peripherals/vga.h"
    "src/peripherals/vga.cc"

    "src/debugger/asm/disassembler.h"
    "src/debugger/asm/disassembler.cc"
    "src/debugger/peripheral.h"
    "src/debugger/peripheral.cc"
    "src/debugger/debugger.h"
    "src/debugger/debugger.cc"

    "src/utils/range.h"
)


# Select the right configuration.
if(MIPSIMU_BUILD_NATIVE)
    add_subdirectory("src/native-app")

    set(SOURCES ${SOURCES} "src/native-app/main.cc")
    link_libraries(mipsimu-native Qt5::Widgets)
else()
    add_subdirectory("src/js-app")

    set(SOURCES ${SOURCES} "src/native-app/main.cc")
    link_libraries(mipsimu-js)    
endif()


# Create the executable
set(CMAKE_BUILD_TYPE Debug)
add_executable(mipsimu ${SOURCES})
