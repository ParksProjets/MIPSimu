#
#  Build MIPSimu tests.
#
#  Copyright (C) 2018, Guillaume Gonnet
#  License MIT

# GNU tools
GCC_PREFIX := /opt/mips-toolchain/bin/mips-sde-elf-
AS = $(GCC_PREFIX)as
CC = $(GCC_PREFIX)gcc
LD = $(GCC_PREFIX)ld
OD = $(GCC_PREFIX)objdump

# Options
BUILD_FOLDER := build
PROG := led-chase
LD_SCRIPT := ldscript.ld
START_SCRIPT := start
OBJDIR := obj
ASSETDIR := assets

# Compile flags
ASFLAGS = -mips32 -EB -mabi=32 -non_shared
CFLAGS = -std=c99 -mips32 -Xassembler -EB -Xassembler -mabi=32 -Xassembler -W -G0 -fno-delayed-branch
LDFLAGS = -G0 -mips3 --static -T $(ASSETDIR)/$(LD_SCRIPT)
ODFLAGS = -d -l --section=.text --section=.data --section=.sdata --section=.bss --section=.rodata --section=.irq_vec


# ELF and Binary data file to generate
DATA_BIN = ../$(BUILD_FOLDER)/data.bin

# Makefile rules
.PHONY: compile run dump clean
.PRECIOUS: $(OBJDIR)/%.o


# Compile a program
compile: $(DATA_BIN)

# Compile and run the test program
run: compile
	../$(BUILD_FOLDER)/mipsimu $(DATA_BIN)

# Dump the program
dump: $(OBJDIR)/$(PROG).elf
	$(OD) $(ODFLAGS) $<


# Make data.bin file
$(DATA_BIN): $(OBJDIR)/$(PROG).elf
	../elf2bin -o $@ $<

# Compile start.s
$(OBJDIR)/$(START_SCRIPT).o: $(ASSETDIR)/$(START_SCRIPT).s
	$(AS) $(ASFLAGS) -G0 -o $@ $<

# Compile .c files
$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile a .s file into an .elf
$(OBJDIR)/%.elf: %.s $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Link all .o file into an .elf
$(OBJDIR)/%.elf: $(OBJDIR)/%.o $(ASSETDIR)/$(LD_SCRIPT) $(OBJDIR)/$(START_SCRIPT).o
	$(LD) $(LDFLAGS) -o $@ $(OBJDIR)/$(START_SCRIPT).o $<


# Create object directory
$(OBJDIR):
	@mkdir $@

# Clean all generated files
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.elf
	rm -f $(DATA_BIN)
