#
#  Build MIPSimu - JS app
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT


# Source files
set(SOURCES

    "system/system.h"
    "system/system.cc"
    "external/screen.h"
    "external/screen.cc"
)

# Include this directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Create the library
add_library(mipsimu-js ${SOURCES})
