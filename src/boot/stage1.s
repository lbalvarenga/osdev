[BITS 16]
[ORG 0x7C00]

s1_main:
  ; https://en.wikipedia.org/wiki/INT_13H#INT_13h_AH=02h:_Read_Sectors_From_Drive
  mov ah, 0x02 ; Read from drive (DL)
  mov al, 0x02 ; 2 * 512 bytes = stage2 size
  xor ch, ch   ; Cylinder 0
  mov cl, 0x02 ; Sector 1 -> stage1; Sector 2..4 -> stage2
  xor dh, dh   ; Head 0

  xor bx, bx
  mov es, bx      ; seg:off (ES:BX) -> (addr) ES * 16 + BX
  mov bx, STAGE_2 ; 0x7E00

  int 0x13

  jmp 0x0000:STAGE_2

TIMES 510 - ($ - $$) db 0
dw 0xAA55

; stage2 is placed right after stage 1, so this works
STAGE_2: