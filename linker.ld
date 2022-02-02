ENTRY(kmain)
OUTPUT_FORMAT(binary)

SECTIONS {
  /* Entrypoint */
  . = 0x10000;

  .text : {
    *(.text.kmain);
    *(.text*);
  }
}