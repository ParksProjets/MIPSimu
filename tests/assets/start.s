.set noreorder

.section __start, "x"  # Standard entry point
    la $gp, _gp	       # Starts the stack at the end of the memory
    move $sp, $gp
    j main
