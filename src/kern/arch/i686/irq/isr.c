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
    idt_entry(idt, i, (uint32_t) &irq_handler_0x00, code_seg,
              IDT_ENTRY_PRESENT | IDT_ENTRY_RING_0 | IDT_GATE_INT32);
  }

  // Fill actual entries
  // Reserved Exceptions and Interrupts 0x00..0x1F
  ISR_RING_0(0x00); ISR_RING_0(0x01); ISR_RING_0(0x02);
  ISR_RING_0(0x03); ISR_RING_0(0x04); ISR_RING_0(0x05);
  ISR_RING_0(0x06); ISR_RING_0(0x07); ISR_RING_0(0x08);
  ISR_RING_0(0x0A); ISR_RING_0(0x0B); ISR_RING_0(0x0C);
  ISR_RING_0(0x0D); ISR_RING_0(0x0E);

  // ISA Interrupts (Remapped from 0x00 to 0x20)
  ISR_RING_0(0x20); ISR_RING_0(0x21);
  ISR_RING_0(0x28);
  ISR_RING_0(0x32);

  // We fill 256 (0x100) entries, so that's our offset
  return idt + 0x100;
}

// TODO: implement stack frame printing

void isr_0xFF() { // Fallback ISR
  kprintf("[FAULT] Interrupt not implemented\n");
  __asm__("cli; hlt");
}

// Reserved Exceptions and Interrupts 0x00..0x1F
void isr_0x00() {
  kprintf("[FAULT] Divide-by-zero Error\n");
  hlt();
}
void isr_0x01() {
  kprintf("[TRAP]  Debug\n");
  hlt();
}
void isr_0x02() {
  kprintf("[INT]   Non-maskable Interrupt\n");
  hlt();
}
void isr_0x03() {
  kprintf("[TRAP]  Breakpoint\n");
  hlt();
}
void isr_0x04() {
  kprintf("[TRAP]  Overflow\n");
  hlt();
}
void isr_0x05() {
  kprintf("[FAULT] Bound Range Exceeded\n");
  hlt();
}
void isr_0x06() {
  kprintf("[FAULT] Invalid Opcode\n");
  hlt();
}
void isr_0x07() {
  kprintf("[FAULT] Device Not Available\n");
  hlt();
}
void isr_0x08() {
  kprintf("[FAULT] Double Fault\n");
  hlt();
}
void isr_0x0A() {
  kprintf("[FAULT] Invalid TSS\n");
  hlt();
}
void isr_0x0B() {
  kprintf("[FAULT] Segment Not Present\n");
  hlt();
}
void isr_0x0C() {
  kprintf("[FAULT] Stack-Segment Fault\n");
  hlt();
}
void isr_0x0D() {
  kprintf("[FAULT] General Protection Fault\n");
  hlt();
}
void isr_0x0E() {
  kprintf("[FAULT] Page Fault\n");
  hlt();
}

// ISA Interrupts (Remapped from 0x00 to 0x20)
void isr_0x20() { // Programmable Interrupt Timer
  pic_eoi(0x20);
}
void isr_0x21() { // Keyboard
  kprintf("[INT] Keyboard interrupt: %x\n", inb(0x60));
  pic_eoi(0x21);
}
void isr_0x28() { // CMOS real-time clock
  pic_eoi(0x28);
}
void isr_0x32() { // PS2 Mouse
  kprintf("[INT] PS2 Mouse interrupt\n");
  pic_eoi(0x32);
}
