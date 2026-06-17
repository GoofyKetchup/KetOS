[BITS 32]

global _start
extern kernel_main
extern _bss_start
extern _bss_end

_start:

    mov esp, 0x00090000 ; stack

    mov edi, _bss_start
    mov ecx, _bss_end
    sub ecx, edi
    xor eax, eax
    rep stosb

    call kernel_main ; call kernel

.halt:
    cli
    hlt
    jmp .halt