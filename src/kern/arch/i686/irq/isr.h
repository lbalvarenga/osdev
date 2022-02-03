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

#endif
