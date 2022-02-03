#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  cli();

  setup_descriptors();

  // disable PIC
  outb(0xA1, 0xFF);
  outb(0x21, 0xFF);
  
  sti();

  // Test interrupt
  int a = 0, b = 2;
  int c = b / a;

  kprintf("%d", c);
  // intr(0x02);

  while (1) {}
  __builtin_unreachable();
}
