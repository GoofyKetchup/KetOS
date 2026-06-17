[BITS 16]
[ORG 0x7C00]

start:
    ; cs = ds
    push cs
    pop ds

    mov [BOOT_DRIVE], dl

    mov si, boot_title
    call print_string

    mov si, option_1
    call print_string

    mov si, option_2
    call print_string

    jmp wait_for_input

print_string:
.next_char:
    mov al, [si]
    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10 ; bios video call
    inc si
    jmp .next_char ; next char
.done:
    ret

; wait for user
wait_for_input:
    mov ah, 0x00
    int 0x16

    cmp al, '1' ; if 1
    je boot_KetOS

    cmp al, '2' ; if 2
    je reboot

    jmp wait_for_input

boot_KetOS:
    mov si, boot_msg
    call print_string

    jmp load_stage2

; load stage2
load_stage2:
    cli

    mov bx, 0x1000
    mov ax, 0x0000
    mov es, ax

    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0x00

    mov dl, [BOOT_DRIVE]

    int 0x13
    jc disk_error

    jmp 0x0000:0x1000

disk_error:
    mov si, boot_fail_msg
    call print_string
    jmp $

reboot:
    mov si, reboot_msg
    call print_string
    int 0x19 ; reboot

; msg & data

boot_title db "[BOOT MENU]", 13, 10, 13, 10, 0

option_1 db "[1] : Continue to KetOS", 13, 10, 0

option_2 db "[2] : Reboot", 13, 10, 13, 10, 0

reboot_msg db "Rebooting...", 13, 10, 0

boot_msg db "Booting KetOS 0.0.1 ...", 13, 10, 0

boot_fail_msg db "Error While Booting.", 13, 10, 0

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xAA55