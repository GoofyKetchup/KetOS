#include "..\drivers\terminal.h"
#include "..\drivers\io.h"
#include "..\lib\console.h"
#include "..\..\os\cli\shell.h"
#include "idt.h"

void kernel_main() {
    __asm__ volatile("cli");
    terminal_print_string((const char*)"Loading...\n");
    idt_init();
    terminal_init();
    terminal_print_string((const char*)"KETOS 0.0.1\n\n");
    __asm__ volatile("sti");
    
    shell_main();

    while(1) {
        __asm__("hlt");
    }
}