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

# Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)


# Source files
set(SOURCES
    "src/core/bus.h"
    "src/core/bus.cc"
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
    "src/debugger/asm/inst_dump.h"
    "src/debugger/asm/inst_dump.cc"
    "src/debugger/peripheral.h"
    "src/debugger/peripheral.cc"
    "src/debugger/debugger.h"
    "src/debugger/debugger.cc"

    "src/utils/range.h"
)


# Select the right configuration.
if(MIPSIMU_BUILD_NATIVE)
    # Build the native app.

    add_definitions(-DMIPSIMU_NATIVE)
    find_package(Qt5Widgets)

    add_subdirectory("src/native-app")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/native-app")

    set(SOURCES ${SOURCES} "src/native-app/main.cc")
    link_libraries(mipsimu-native Qt5::Widgets)

else()
    # Build the JS app using Emscripten.

    if (NOT EMSCRIPTEN)
        message(FATAL_ERROR "Emscripten toolschain not found. See README for more information.")
    endif()

    add_definitions(-DMIPSIMU_JS)

    add_subdirectory("src/js-app")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/js-app")

    set(SOURCES ${SOURCES} "src/js-app/main.cc")
    link_libraries(mipsimu-js)    

endif()


# Create the executable
add_executable(mipsimu ${SOURCES})
