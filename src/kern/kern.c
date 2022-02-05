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
  pic_init(0x20, 0x28); // Programmable Interrupt Controller
  fb_init();            // Framebuffer

  // Restore interrupts
  sti();

  // We made it :)
  kprintf("\n");
  kprintf("  _       _         _____ _____  \n");
  kprintf(" | |_ ___| |_ _ _ _|     |   __| \n");
  kprintf(" | '_| -_| '_| | | |  |  |__   | \n");
  kprintf(" |_,_|___|_,_|_____|_____|_____| \n");
  kprintf("                                 \n\n");
  kprintf(" An OS so bad you can't not laugh \n\n");
  kprintf("C:\\> ");
                               

  while (1) {}
  __builtin_unreachable();
}
