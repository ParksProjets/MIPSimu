# MIPSimu

## Introduction

**MIPSimu** is a basic MIPS processor emulator. It supports only a subset of the
MIPS III instruction set. It emulates a **non-pipelined** MIPS processor.

**MIPSimu** has the following peripherals:
- VGA 320x240 screen
- CPU timer
- 4 LEDs
- 3 push buttons
- debuggers

For more information, you can see [here][mips-periphs] the documentation about
these peripherals.

As the processor has not pipeline, each instruction takes a different number of
cycles to be executed. You can find [on this page][mips-inst] all supported MIPS
instructions and the number of cycles for each instruction.



## Build MIPSimu

**MIPSimu** requires **Qt 5.2** (or newer).  
Also must you have **cmake** to build the application (minimum version required
is **3.3**).



## Run the tests

**MIPSimu** has two kind of tests: unit tests and real program tests, respectively
in the `unittests` and `tests` folders.

### Unit tests

The tests use the **QTest** module from **Qt**.



### Real program tests



## License

This project is under the MIT license.  
You can find the whole license the file named `LICENSE` at the root of the
repository.

This project is based on [CamelusMips][CamelusMips], under the MIT license.



[mips-periphs]: docs/peripherals.md
[mips-inst]: docs/instructions.md

[CamelusMips]: https://github.com/MForever78/CamelusMips
