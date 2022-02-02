__attribute__((noreturn)) void kmain() {
  volatile char* video = (volatile char* ) 0xB8000;

  *video++ = '!';
  *video++ = 0x02;

  while (1) {}
  __builtin_unreachable();
}