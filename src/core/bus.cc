/*

The processor bus.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "core/bus.h"

namespace core {


// Add a another peripheral in the bus.
void Bus::Add(Peripheral *peripheral, utils::range<uint32_t> range)
{
    auto it = peripherals_.begin();
    auto end = peripherals_.end();

    while (it != end && it->first < range)
        it++;

    peripherals_.insert(it, std::make_pair(range, peripheral));
}



// Get the peripheral mapped at the address given.
Bus::Plugged *Bus::Get(uint32_t addr)
{
    for (auto &pair : peripherals_) {
        if (pair.first.contains(addr))
            return &pair;
    }

    return nullptr;
}



// Set a value at the address given.
void Bus::SetValue(uint32_t addr, uint32_t value)
{
    Plugged *plugged = Get(addr);

    if (plugged)
        plugged->second->SetValue(plugged->first.translate(addr), value);
}



// Get the value the address given.
uint32_t Bus::GetValue(uint32_t addr)
{
    Plugged *plugged = Get(addr);

    if (plugged)
        return plugged->second->GetValue(plugged->first.translate(addr));
    return 0;
}


} // namespace core
