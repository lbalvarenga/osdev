#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"
#include "arch/i686/pic/pic.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  // Clear interrupts if not already
  cli();

  // Sets up GDT, IDT and ISRs
  setup_descriptors();
  // pic_disable();
  pic_init(0x20, 0x28);
  
  // Restore interrupts
  sti();

  kprintf("[INFO]  %s() @ %x\n", __func__, &kmain);

  // Trigger fault (div by 0)
  // int b = 0;
  // int a = (1 + 1)/b;
  // kprintf("%d", a);

  while (1) {}
  __builtin_unreachable();
}
