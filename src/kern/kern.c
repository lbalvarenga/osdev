#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  // Clear interrupts if not already
  cli();

  // Sets up GDT, IDT and ISRs
  setup_descriptors();

  // disable PIC
  outb(0xA1, 0xFF);
  outb(0x21, 0xFF);
  
  // Restore interrupts
  sti();

  // Trigger fault (div by 0)
  int b = 0;
  int a = (1 + 1)/b;
  kprintf("%d", a);

  while (1) {}
  __builtin_unreachable();
}
