[BITS 16]
[ORG 0x7E00]

%define CODE_SEG (gdt_code - gdt_start)
%define DATA_SEG (gdt_data - gdt_start)

s2_main:
  ; TODO: enable A20

  ; Load kernel
  mov ah, 0x02
  mov al, 0x80 ; Plenty of room for kernel
  xor ch, ch   ; Cylinder 0
  mov cl, 0x04 ; Sector 2..3 -> stage2; Sector 4..132 -> kernel
  xor dh, dh

  mov bx, 0x1000
  mov es, bx
  xor bx, bx ; 0x10000

  int 0x13

  ; Set video mode 0x03
  xor ah, ah
  mov al, 0x03

  int 0x10

  cli
  ; Load memory descriptor
  lgdt [gdt_desc]

  ; Switch to protected mode
  mov eax, cr0
  or eax, 0x01
  mov cr0, eax

  ; Clear instruction pipeline (far jmp)
  jmp CODE_SEG:pmode

[BITS 32]
pmode:
  ; Set segment registers to data segment defined by gdt
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ; Relocate stack
  mov esp, 0x80000
  mov ebp, esp

  ; Jump to kernel entrypoint
  jmp 0x10000

%include "desc/gdt.inc"

TIMES 1024 - ($ - $$) db 0x00
