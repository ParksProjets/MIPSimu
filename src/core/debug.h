/*

Some useful macro for debugging.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once


#ifdef MIPSIMU_NATIVE
    // If we have Qt, we use qWarning for debugging.

    #include <QtCore/QtGlobal>

    #define warn qWarning

#else
    // Else, we do a printf of the message.

    #include <stdio.h>

    #define warn printf

#endif
