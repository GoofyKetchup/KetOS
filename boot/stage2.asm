[BITS 16]
[ORG 0x1000]

start:
    mov [BOOT_DRIVE], dl
    call load_gdt
    call enable_a20
    call load_krnl
    jmp enable_pm

; a20 to access +1MB
enable_a20:
    cli
    in al, 0x92
    or al, 2
    out 0x92, al
    ret 

load_krnl:
    cli

    xor ax, ax
    mov ds, ax

    ; test if bios disk extension are supported

    mov ah, 0x41
    mov bx, 0x55AA
    mov dl, [BOOT_DRIVE]

    int 0x13 ; bios disk call
    jc no_extended

    ; check bx
    cmp bx, 0xAA55
    jne no_extended

    
    mov ah, 0x42
    mov si, dap
    mov dl, [BOOT_DRIVE]

    int 0x13 ; bios disk call
    jc disk_error

    ret

enable_pm:
    mov eax, cr0
    or eax, 1
    mov cr0, eax ; pm activated

    jmp 0x08:PM_ENTRY

no_extended: ; if bios extension are not supported
    mov si, EXTENDED_BIOS_NOT_SUPPORTED
    call print_string
    cli
    hlt
    jmp $

disk_error: ; if error while reading the disk
    mov si, DISK_ERROR_MSG
    call print_string
    cli
    hlt
    jmp $

print_string:
.next_char:
    mov al, [si]
    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10 ; bios video call
    inc si
    jmp .next_char
.done:
    ret

dap: ; disk adressing packet table
    db 0x10
    db 0
    dw 128
    dw 0x0000
    dw 0x8000
    dq 2

%include "boot/gdt.asm" ; gdt

[BITS 32]
PM_ENTRY:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x70000

MOV_KERNEL:

    cld

    mov esi, 0x80000
    mov edi, 0x100000
    mov ecx, 0x20000

    rep movsb ; mov kernel from 0x80000 to 0x100000

    jmp 0x08:0x100000

BOOT_DRIVE db 0
EXTENDED_BIOS_NOT_SUPPORTED db "Sorry, Your device is not compatible with KetOS.", 13, 10, 0
DISK_ERROR_MSG db "Sorry, An error occured while reading disk", 13, 10, 0

times 512-($-$$) db 0