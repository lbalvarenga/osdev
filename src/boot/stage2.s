[BITS 16]
[ORG 0x7E00]

jmp main

main:
  jmp $

TIMES 1024 - ($ - $$) db 0