#
#  Build MIPSimu unit tests.
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT

cmake_minimum_required(VERSION 3.3)
project(mipsimu-unittests)

enable_testing()


# Include current directory and 'src' directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../src")

# Tells CMake to run moc automatically
set(CMAKE_AUTOMOC ON)

# Import Qt5
find_package(Qt5Widgets)
find_package(Qt5Test)


# Add a new MIPSimu test.
macro(add_mipsimu_test name)
    add_executable(${name} ${ARGN})
    add_test(${name} foo)

    target_link_libraries(${name} Qt5::Widgets Qt5::Test)
endmacro()


# Test: core :: Disassembler
add_mipsimu_test(test-core-disassembler
    "../src/core/disassembler.h"
    "../src/core/disassembler.cc"
    "test_core_disassembler.cc"
)


# Test: core :: Bus
add_mipsimu_test(test-core-bus
    "../src/core/bus.h"
    "../src/core/bus.cc"
    "test_core_bus.cc"
)


# Test: core :: Processor
add_mipsimu_test(test-core-processor
    "../src/core/disassembler.h"
    "../src/core/disassembler.cc"
    "../src/core/processor.h"
    "../src/core/processor.cc"
    "../src/core/bus.h"
    "../src/core/bus.cc"
    "test_core_processor.cc"
)
