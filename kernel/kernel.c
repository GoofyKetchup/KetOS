#include "..\drivers\vga.h"
#include "..\lib\vga_utils.h"
#include "idt.h"

void kernel_main() {

    vga_print("Loading IDT...\n");

    idt_init();

    vga_print("Setting up Paging...\n");

    while(1) {
        __asm__("hlt");
        }
}