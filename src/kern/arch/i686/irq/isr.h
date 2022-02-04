#ifndef I686_ISR_H
#define I686_ISR_H

#include "arch/i686/descriptor.h"

#define ISR_RING_0(i) idt_entry(idt, (uint32_t) &irq_handler_##i, code_seg, \
                      IDT_GATE_INT32 | IDT_ENTRY_RING_0 | IDT_ENTRY_PRESENT)

void register_isrs(IDT_TABLE** idt, uintptr_t code_seg);

extern void irq_handler_0x00();
extern void irq_handler_0x01();
extern void irq_handler_0x02();
extern void irq_handler_0x03();
extern void irq_handler_0x04();
extern void irq_handler_0x05();
extern void irq_handler_0x06();
extern void irq_handler_0x07();
extern void irq_handler_0x08();
extern void irq_handler_0x09();
extern void irq_handler_0x0A();
extern void irq_handler_0x0B();
extern void irq_handler_0x0C();
extern void irq_handler_0x0D();
extern void irq_handler_0x0E();
extern void irq_handler_0x0F();
extern void irq_handler_0x10();
extern void irq_handler_0x11();
extern void irq_handler_0x12();
extern void irq_handler_0x13();
extern void irq_handler_0x14();
extern void irq_handler_0x15();
extern void irq_handler_0x16();
extern void irq_handler_0x17();
extern void irq_handler_0x18();
extern void irq_handler_0x19();
extern void irq_handler_0x1A();
extern void irq_handler_0x1B();
extern void irq_handler_0x1C();
extern void irq_handler_0x1D();
extern void irq_handler_0x1E();
extern void irq_handler_0x1F();

#endif
