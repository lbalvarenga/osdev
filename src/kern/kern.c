#include "arch/i686/descriptor.h"
#include "arch/i686/asm/asm.h"

#include "std/stdio.h"

__attribute__((noreturn)) void kmain() {
  cli();

  #define GDT_BASE 0x100000

  // TODO: place in other file and choose a proper address
  TABLE_GDT* gdt = (TABLE_GDT* ) GDT_BASE;
  gdt_entry(&gdt, 0, 0, 0, 0);

  gdt_entry(&gdt,
  0x000FFFFF, 0x00000000,                         // Limit, Base
  GDT_FLAG_GRAN   | GDT_FLAG_SIZE  ,              // Flags
  GDT_SEG_PRESENT | GDT_SEG_RING_0 |              // Access
  GDT_SEG_NOT_TSS | GDT_SEG_EXEC   | GDT_SEG_RW); // Access

  gdt_entry(&gdt,
  0x000FFFFF, 0x00000000,             // Limit, Base
  GDT_FLAG_GRAN   | GDT_FLAG_SIZE  ,  // Flags
  GDT_SEG_PRESENT | GDT_SEG_RING_0 |  // Access
  GDT_SEG_NOT_TSS | GDT_SEG_RW     ); // Access

  TABLE_IDT* idt = (TABLE_IDT* ) register_gdt(gdt, GDT_BASE);

  idt_entry(&idt, 0x00, 0x10, 0x00);

  kprintf("[INFO] Loaded at %x\n", &kmain);
  
  // sti();

  while (1) {}
  __builtin_unreachable();
}