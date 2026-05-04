[BITS 16]
[ORG 0x1000]

start:
    mov si, loading_GDT_msg
    call print_string

    call load_gdt
    
    mov si, enabling_a20_msg
    call print_string

    call enable_a20

    mov si, enabling_pm_msg
    call print_string

    call load_kernel

    call enable_pm

enable_a20:
    cli
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

gdt_start:

gdt_null:
    dq 0x0000000000000000

gdt_kernel_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_kernel_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_user_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 11111010b
    db 11001111b
    db 0x00

gdt_user_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 11110010b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

load_gdt:
    cli
    lgdt [gdt_descriptor]
    ret

load_kernel:
    cli

    mov [BOOT_DRIVE], dl

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

print_string:
.next_char:
    mov al, [si]
    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10
    inc si
    jmp .next_char
.done:
    ret

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

loading_GDT_msg db "Loading GDT...", 13, 10, 0

enabling_a20_msg db "Enabling A20...", 13, 10, 0

enabling_pm_msg db "Enabling Protected Mode...", 13, 10, 0

BOOT_DRIVE db 0

times 512-($-$$) db 0