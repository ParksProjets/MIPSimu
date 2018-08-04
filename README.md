# MIPSimu

![](docs/flapsthemips.gif)

Find this game with some other applications in [Mips-Applications][apps]
repository.



## Introduction

**MIPSimu** is a basic MIPS processor emulator. It supports only a subset of the
MIPS III instruction set. It emulates a **non-pipelined** MIPS processor.

**MIPSimu** has the following peripherals:
- two RAMs
- VGA 320x240 screen
- CPU timer
- 4 LEDs
- 3 push buttons
- debugger

For more information, you can see [here][mips-periphs] the documentation about
these peripherals.

As the processor has not pipeline, each instruction takes a different number of
cycles to be executed. You can find [on this page][mips-inst] all supported MIPS
instructions and the number of cycles for each instruction.



## Build MIPSimu

**MIPSimu** requires **CMake** (version **3.3** or newer).  
It has two CMake options:

- `MIPSIMU_BUILD_NATIVE` – `ON` to build the native Qt app, `OFF` for the JS app
- `MIPSIMU_ENABLE_TESTS` – `ON` to build unit tests.

The **native app** and the **unit tests** require **Qt 5.2** (or newer).

The **js app** requires **[emscripten][emscripten]**. Before running CMake,
specifying the toolchain file with CMake variable
`CMAKE_TOOLCHAIN_FILE=<ensdk>/emscripten/version/cmake/Modules/Platform/Emscripten.cmake`.



## Run the tests

**MIPSimu** has two kind of tests: unit tests and real program tests, respectively
in the `unittests` and `tests` folders.


### Unit tests

The tests use the **QTest** module from **Qt**. To build these tests set CMake
`MIPSIMU_ENABLE_TESTS` option to `ON`.  
Each test generate a different executable that you can run.


### Real program tests

You can test some "real" programs that use the whole emulator in `tests` directory.
These tests require **GNU toolchain** for MIPS in order to cross-compile C programs
to MIPS.



## License

This project is under the MIT license.  
You can find the whole license in the file named `LICENSE` at the root of the
repository.



[mips-periphs]: docs/peripherals.md
[mips-inst]: docs/instructions.md

[apps]: https://github.com/ParksProjets/Mips-Applications
[emscripten]: http://kripken.github.io/emscripten-site/index.html
