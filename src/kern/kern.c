#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"
#include "arch/i686/pic/pic.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  // Clear interrupts if not already
  cli();

  // Sets up GDT, IDT and ISRs
  setup_descriptors();

  // Initialize devices
  pic_init(0x20, 0x28);

  // Restore interrupts
  sti();

  // We made it :)
  kprintf("[INFO]  %s() @ %x\n", __func__, &kmain);

  while (1) {}
  __builtin_unreachable();
}
