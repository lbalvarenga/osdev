#include "isr.h"
#include "arch/i686/descriptor.h"

#include "std/stdio.h"

void register_isrs(IDT_TABLE** idt, uintptr_t code_seg) {
  ISR_RING_0(0x00);
  ISR_RING_0(0x01);
  ISR_RING_0(0x02);
  ISR_RING_0(0x03);
  ISR_RING_0(0x04);
  ISR_RING_0(0x05);
  ISR_RING_0(0x06);
}

// TODO: implement stack frame printing

void isr_0x00() { // [FAULT]      Divide-by-zero Error
  kprintf("[FAULT] Divide-by-zero (INT 0x00)\n");
  __asm__("cli; hlt");
}
void isr_0x01() { // [FAULT/TRAP] Debug
  kprintf("Hello from interrupt 0x01!\n");
}
void isr_0x02() { // [INTERRUPT]  Non-maskable Interrupt
  kprintf("Hello from interrupt 0x02!\n");
}
void isr_0x03() { // [TRAP]       Breakpoint
  kprintf("Hello from interrupt 0x03!\n");
}
void isr_0x04() { // [TRAP]       Overflow
  kprintf("Hello from interrupt 0x04!\n");
}
void isr_0x05() { // [FAULT]      Bound Range Exceeded
  kprintf("Hello from interrupt 0x05!\n");
}
void isr_0x06() { // [FAULT]      Invalid Opcode
  kprintf("[FAULT] Invalid Opcode (INT 0x06)\n");
  __asm__("cli; hlt");
}
