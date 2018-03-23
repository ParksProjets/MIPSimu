/*

Load the RAM memory.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "peripherals/ram.h"

#include <QtCore/QString>

namespace app {


// Load the RAM memory.
class MemoryLoader {
public:

    MemoryLoader(peripherals::Ram &ram, peripherals::Ram &ram2, bool use_ram2);


    // Load a file into the memory.
    void Load(const QString &filename);


private:

    peripherals::Ram &ram_;
    peripherals::Ram &ram2_;

    bool use_ram2_;
};


} // namespace app
