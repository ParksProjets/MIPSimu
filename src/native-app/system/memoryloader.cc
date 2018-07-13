/*

Load the RAM memory.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/memoryloader.h"

#include <QtCore/QFile>
#include <QtCore/QtEndian>

#include <string.h>

namespace app {


// Constructor.
MemoryLoader::MemoryLoader(peripherals::Ram &ram, peripherals::Ram &ram2, bool use_ram2)
    : ram_{ram},
      ram2_{ram2},
      use_ram2_{use_ram2}
{

}



// Load a file into the memory.
void MemoryLoader::Load(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
        qFatal("Can't load RAM data.");

    if (!use_ram2_ && file.size() > ram_.size())
        qFatal("RAM to small (%dB) for program data (%dB)", ram_.size(), file.size());

    uint32_t *buffer = ram_.buffer();
    uint32_t readed = file.read(reinterpret_cast<char *>(buffer), ram_.size());

    for (int i = 0; i < readed / 4; i++)
        qToBigEndian(buffer[i], reinterpret_cast<uchar *>(buffer + i));

    if (use_ram2_) {
        file.seek(0x20000);
        uint32_t *buffer = ram2_.buffer();
        uint32_t readed = file.read(reinterpret_cast<char *>(buffer), ram2_.size());

        for (int i = 0; i < readed / 4; i++)
            qToBigEndian(buffer[i], reinterpret_cast<uchar *>(buffer + i));
    }

    file.close();
}


} // namespace app
