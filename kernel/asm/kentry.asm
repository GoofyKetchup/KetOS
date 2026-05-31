[BITS 32]
section .text
global _start

extern kernel_main

_start:
    cli

    nop

    call kernel_main