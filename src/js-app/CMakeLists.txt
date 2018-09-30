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


# Add custom target for copying files from "html" folder.
add_custom_target(copy-html)

file(GLOB FILES_TO_COPY "${CMAKE_CURRENT_SOURCE_DIR}/html/*")

foreach(FILE ${FILES_TO_COPY})
    add_custom_command(TARGET copy-html PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy "${FILE}" "${CMAKE_BINARY_DIR}")
endforeach()
