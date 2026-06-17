nasm -f bin boot/bootloader.asm -o bootloader.bin
nasm -f bin boot/stage2.asm -o stage2.bin

nasm -f elf32 kernel/asm/kentry.asm -o kentry.o
nasm -f elf32 kernel/asm/isr.asm -o isr.o

i686-elf-gcc.exe -m32 -ffreestanding -c kernel/core/kernel_main.c -o kernel_main.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/core/idt.c -o idt.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/drivers/io.c -o io.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/drivers/terminal.c -o terminal.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/lib/ascii.c -o ascii.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/lib/console.c -o console.o
i686-elf-gcc.exe -m32 -ffreestanding -c kernel/lib/string.c -o string.o
i686-elf-gcc.exe -m32 -ffreestanding -c os/cli/shell.c -o shell.o

i686-elf-ld.exe -T linker/linker.ld -o ketoskrnl.elf^
 kentry.o kernel_main.o^
 io.o terminal.o^
 ascii.o console.o string.o^
 isr.o idt.o^
 shell.o

i686-elf-objcopy.exe -O binary ketoskrnl.elf ketoskrnl.bin

i686-elf-nm.exe ketoskrnl.elf | findstr "_start"

powershell -ExecutionPolicy Bypass -File build_img.ps1

del ascii.o, bootloader.bin, console.o, idt.o, io.o, isr.o, kentry.o, kernel_main.o, ketoskrnl.bin, ketoskrnl.elf, shell.o, stage2.bin, string.o, terminal.o

pause

qemu-system-i386 -cpu 486 -m 2048 -drive file=ketos.img,format=raw