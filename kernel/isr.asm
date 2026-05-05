extern isr_handler
global isr0
global isr_default

isr0:
    cli
    pusha

    push 0
    call isr_handler
    add esp, 4

    popa
    sti
    iret

isr_default:
    cli
    pusha

    push 255
    call isr_handler
    add esp, 4

    popa
    sti
    iret