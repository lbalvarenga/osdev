#include "isr.h"
#include "arch/i686/descriptor.h"

// TODO: determine if PIC is enabled
#include "arch/i686/pic/pic.h"

#include "std/stdio.h"

// redirecting to 0x00 for testing
void register_isrs(IDT_TABLE** idt, uintptr_t code_seg) {
  for (int i = 0; i < 256; ++i) {
    idt_entry(idt, (uint32_t) &irq_handler_0x00, code_seg,
              IDT_GATE_INT32 | IDT_ENTRY_RING_0 | IDT_ENTRY_PRESENT);
  }
}

// TODO: implement stack frame printing

void isr_0x00() { // [FAULT]      Divide-by-zero Error
  kprintf("[FAULT] Divide-by-zero (IRQ %x)\n", pic_get_irq());
  pic_eoi(0x00);
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
  kprintf("[FAULT] Invalid Opcode (%s)\n", __func__);
  __asm__("cli; hlt");
}
