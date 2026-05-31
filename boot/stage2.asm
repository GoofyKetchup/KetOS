[BITS 16]
[ORG 0x1000]

start:
    mov [BOOT_DRIVE], dl
    call load_gdt
    call enable_a20
    call load_kernel
    call enable_pm

enable_a20:
    cli
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

load_kernel:
    cli

    mov ax, 0x1000
    mov es, ax
    mov bx, 0x0000

    mov ah, 0x02
    mov al, 32
    mov ch, 0
    mov cl, 3
    mov dh, 0
    mov dl, [BOOT_DRIVE]

    int 0x13

    ret

enable_pm:
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:PM_ENTRY

%include "boot/gdt.asm"

[BITS 32]
PM_ENTRY:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    cld

    jmp 0x08:0x10000

BOOT_DRIVE db 0

times 512-($-$$) db 0