[BITS 16]
[ORG 0x7C00]

jmp main

main:
  jmp $

TIMES 510 - ($ - $$) db 0
db 0xAA55