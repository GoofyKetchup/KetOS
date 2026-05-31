#include "..\drivers\terminal.h"
#include "..\drivers\io.h"
#include "..\lib\console.h"
#include "..\..\os\cli\shell.h"
#include "idt.h"

void kernel_main() {

    terminal_print_string((const char*)"Loading...\n");

    idt_init();

    terminal_init();

    terminal_print_string((const char*)"KETOS 0.1.2\n\n");

    shell_main();

    while(1) {
        __asm__("hlt");
    }
}