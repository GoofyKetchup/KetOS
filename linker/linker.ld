ENTRY(_start)

SECTIONS
{
    . = 0x1M;

    .text ALIGN(4096) : { *(.text*) }
    .rodata ALIGN(4096) : { *(.rodata*) }
    .data ALIGN(4096) : { *(.data*) }
    .bss ALIGN(4096) : {
        _bss_start = .;
        *(.bss*)
        *(COMMON) 
        _bss_end = .;
    }

    _kernel_end = .;
}