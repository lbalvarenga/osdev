#include "isr.h"
#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"

// TODO: determine if PIC is enabled
#include "arch/i686/pic/pic.h"

#include "std/stdio.h"

// Not the most efficient function ever...
IDT_TABLE* register_isrs(IDT_TABLE* idt, uintptr_t code_seg) {
  // Fill entries with fallback ISR
  for (int i = 0; i < 256; ++i) {
    idt_entry(idt, i, (uint32_t) &irq_handler_0xFF, code_seg,
              IDT_ENTRY_PRESENT | IDT_ENTRY_RING_0 | IDT_GATE_INT32);
  }

  // Fill actual entries
  ISR_RING_0(0x0A);

  // We fill 256 (0x100) entries, so that's our offset
  return idt + 0x100;
}

// TODO: implement stack frame printing

// Fallback ISR
void isr_0xFF() {
  kprintf("[FAULT] Interrupt not implemented\n");
  __asm__("cli; hlt");
}

void isr_0x0A() {
  kprintf("You're winner!\n");
}
