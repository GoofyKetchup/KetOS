extern isr0_handler
extern isr_default_handler
global isr0
global isr_default

isr0:
    cli
    pusha

    call isr0_handler

    popa
    sti
    iret

isr_default:
    cli
    pusha

    call isr_default_handler

    popa
    sti
    iret