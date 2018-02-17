#
#  Build MIPSimu
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT

cmake_minimum_required(VERSION 3.3)
project(mipsimu)


# Unit tests
option(ENABLE_MIPSIMU_TESTS "Enable MIPSimu unit tests." OFF)
if(ENABLE_MIPSIMU_TESTS)
    add_subdirectory(unittests)
endif()


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
    "src/app/mainwindow.h"
    "src/app/mainwindow.cc"

    "src/debugger/asm/disassembler.h"
    "src/debugger/asm/disassembler.cc"
    "src/debugger/peripheral.h"
    "src/debugger/peripheral.cc"
    "src/debugger/debugger.h"
    "src/debugger/debugger.cc"

    "src/utils/range.h"
    "src/main.cc"
)


# Create the executable
set(CMAKE_BUILD_TYPE Debug)
add_executable(mipsimu ${SOURCES})

# Link libraries.
target_link_libraries(mipsimu
    Qt5::Widgets
)
