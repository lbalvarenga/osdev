# arch/i686/irq

The way this works is a little different. The IDT contains references
to assembly-defined subroutines. Those subroutines, in turn, call the
appropriate C-defined handlers. That is why the header file only contains
external references. The functions in [isr.c] are called from assembly,
so they don't need to be defined anywhere else.
