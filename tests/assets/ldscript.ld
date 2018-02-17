SECTIONS
{
    . = 0x000;
    .text : { *(__start) } 
    .text : { *(.text) }  
    .data : { *(.data) }
    .sdata : { *(.sdata) }
    _edata = .;
    .bss : { *(.bss)  }
    . = 0x1FFC;
    _gp = .;
    .irq_vec : { *(.irq_vec)}
}