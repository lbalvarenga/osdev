#include "drv/gfx/vga.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  kprintf("[INFO] Kernel loaded @ %x\n", &kmain);

  while (1) {}
  __builtin_unreachable();
}