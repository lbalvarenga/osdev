#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"
#include "arch/i686/pic/pic.h"
#include "drv/gfx/fbdev.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  // Clear interrupts if not already
  cli();

  // Sets up GDT, IDT and ISRs
  setup_descriptors();

  // Initialize devices
  pic_init(0x20, 0x28);
  fb_init();

  // Restore interrupts
  sti();

  // We made it :)

  extern uint8_t* FB_COLOR;
  *FB_COLOR = (0x01 << 4) | 0x0F;
  fb_clear(*FB_COLOR);

  // for (int i = 0; i < 25; ++i) {
  //   kprintf("testtestestesteteesee\n");
  // }

  while (1) {}
  __builtin_unreachable();
}
