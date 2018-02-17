/*

Load the RAM memory.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "app/memoryloader.h"

#include <QtCore/QFile>
#include <QtCore/QtEndian>

#include <string.h>

namespace app {


// Constructor.
MemoryLoader::MemoryLoader(peripherals::Ram &ram)
    : ram_{ram}
{

}



// Load a file into the memory.
void MemoryLoader::Load(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
        qFatal("Can't load RAM data.");

    if (file.size() > ram_.size())
        qFatal("RAM to small (%dB) for program data (%dB)", ram_.size(), file.size());

    uint32_t *buffer = ram_.buffer();
    uint32_t readed = file.read(reinterpret_cast<char *>(buffer), ram_.size());
    file.close();

    for (int i = 0; i < readed / 4; i++)
        qToBigEndian(buffer[i], reinterpret_cast<uchar *>(buffer + i));
}


} // namespace app
