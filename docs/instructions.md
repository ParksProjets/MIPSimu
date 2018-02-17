# Supported instructions

You will find below the list of supported instructions, as well as the number of
cycles necessary to execute these instructions.

You can find all MIPS instructions on the following links:
- [University of Idaho][uidaho.edu].
- [MIPT-ILab][mipt-ilab]


| Name    | Full name                               | Supported?   | Number of cycles |
|:-------:| --------------------------------------- |:------------:|:----------------:|
| ADD     | Add (with overflow)                     | Yes          |         3        |
| ADDI    | Add immediate (with overflow)           | Yes          |         3        |
| ADDIU   | Add immediate unsigned (no overflow)    | Same as ADDI |         3        |
| ADDU    | Add unsigned (no overflow)              | Same as ADD  |         3        |
| AND     | Bitwise and                             | Yes          |         3        |
| ANDI    | Bitwise and immediate                   | Yes          |         3        |
| BEQ     | Branch on equal                         | Yes          |      4 or 5      |
| BGEZ    | Branch on greater than or equal to zero | Yes          |      4 or 5      |
| BGEZAL  | Branch on >= 0 and link                 | Yes          |      5 or 6      |
| BGTZ    | Branch on greater than zero             | Yes          |      4 or 5      |
| BLEZ    | Branch on less than or equal to zero    | Yes          |      4 or 5      |
| BLTZ    | Branch on less than zero                | Yes          |      4 or 5      |
| BLTZAL  | Branch on less than zero and link       | Yes          |      5 or 6      |
| BNE     | Branch on not equal                     | Yes          |      4 or 5      |
| BREAK   | Breakpoint                              | No           |        N/A       |
| DIV     | Divide                                  | No           |        N/A       |
| DIVU    | Divide unsigned                         | No           |        N/A       |
| ERET    | Exception return                        | No           |        N/A       |
| J       | Jump                                    | Yes          |         4        |
| JAL     | Jump and link                           | Yes          |         5        |
| JALR    | Jump register and link                  | Yes          |         5        |
| JR      | Jump register                           | Yes          |         4        |
| LB      | Load byte                               | No           |        N/A       |
| LBU     | Load byte unsigned                      | No           |        N/A       |
| LH      | Load half word                          | No           |        N/A       |
| LHU     | Load half word unsigned                 | No           |        N/A       |
| LUI     | Load upper immediate                    | Yes          |         3        |
| LW      | Load word                               | Yes          |         6        |
| MFC0    | Move from coprocessor 0                 | No           |        N/A       |
| MFHI    | Move from HI                            | No           |        N/A       |
| MFLO    | Move from LO                            | No           |        N/A       |
| MFT0    | Move to coprocessor 0                   | No           |        N/A       |
| MTHI    | Move to HI                              | No           |        N/A       |
| MFLO    | Move to LO                              | No           |        N/A       |
| MULT    | Multiply                                | No           |        N/A       |
| MULTU   | Multiply unsigned                       | No           |        N/A       |
| NOR     | Bitwise nor                             | Yes          |         3        |
| OR      | Bitwise or                              | Yes          |         3        |
| ORI     | Bitwise or immediate                    | Yes          |         3        |
| SB      | Store byte                              | No           |        N/A       |
| SH      | Store half word                         | No           |        N/A       |
| SLL     | Shift left logical                      | Yes          |         3        |
| SLLV    | Shift left logical variable             | Yes          |         3        |
| SLT     | Set on less than (signed)               | Yes          |         4        |
| SLTI    | Set on less than immediate (signed)     | Yes          |         4        |
| SLTIU   | Set on less than immediate unsigned     | Yes          |         4        |
| SLTU    | Set on less than unsigned               | Yes          |         4        |
| SRA     | Shift right arithmetic                  | Yes          |         3        |
| SRAV    | Shift right arithmetic variable         | Yes          |         3        |
| SRL     | Shift right logical                     | Yes          |         3        |
| SRLV    | Shift right logical variable            | Yes          |         3        |
| SUB     | Subtract                                | Yes          |         3        |
| SUBU    | Subtract unsigned                       | Same as SUB  |         3        |
| SW      | Store word                              | Yes          |         6        |
| SYSCALL | System call                             | No           |        N/A       |
| XOR     | Bitwise exclusive or                    | Yes          |         3        |
| XORI    | Bitwise exclusive or immediate          | Yes          |         3        |


[uidaho.edu]: http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html
[mipt-ilab]: https://github.com/MIPT-ILab/mipt-mips/wiki/MIPS-Instruction-Set
