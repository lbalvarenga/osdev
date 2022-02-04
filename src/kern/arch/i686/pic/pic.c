#include "pic.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// This can be changed according to OS's needs
// Master -> 0..7, Slave -> 8..15
// off_slave >= off_master + 8
void pic_init(uint8_t off_master, uint8_t off_slave) {
  // Save masks
  uint8_t mask_master = inb(PIC_MASTER_DATA);
  uint8_t mask_slave  = inb(PIC_SLAVE_DATA );

  // Sequence start (by sungazer)
  outb(PIC_MASTER_CMD, PIC_ICW1_INIT);     io_wait();
  outb(PIC_SLAVE_CMD,  PIC_ICW1_INIT);     io_wait();

  outb(PIC_MASTER_DATA, off_master);       io_wait();
  outb(PIC_SLAVE_DATA,  off_slave);        io_wait();

  outb(PIC_MASTER_DATA, PIC_SLAVE_OFFSET); io_wait();
  outb(PIC_SLAVE_DATA,  PIC_SLAVE_IDENT ); io_wait();

  outb(PIC_MASTER_DATA, PIC_MODE_8086);    io_wait();
  outb(PIC_SLAVE_DATA,  PIC_MODE_8086);    io_wait();

  // Restore masks
  outb(PIC_MASTER_DATA, mask_master);
  outb(PIC_SLAVE_DATA,  mask_slave );
}

void pic_disable() {
  outb(PIC_SLAVE_DATA,  0xFF);
  outb(PIC_MASTER_DATA, 0xFF);
}

void pic_eoi(uint8_t irq) {
  // Check if irq comes from slave
  if (irq >= 8) {
    outb(PIC_SLAVE_CMD, PIC_EOI);
  }

  outb(PIC_MASTER_CMD, PIC_EOI);
}

uint16_t pic_get_irq() {
  outb(PIC_MASTER_CMD, 0x0B);
  outb(PIC_SLAVE_CMD,  0x0B);
  return (inb(PIC_SLAVE_CMD) << 8) | inb(PIC_MASTER_CMD);
}
