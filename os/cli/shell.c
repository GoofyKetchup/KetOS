#include <stdint.h>
#include "..\..\kernel\lib\console.h"
#include "..\..\kernel\lib\string.h"
#include "..\..\kernel\core\idt.h"

void execute_command(const char* cmd) {
    int cping = cmp_str(cmd, (const char*)"ping");
    if (cping == 1) {
        terminal_print_string("Pong.");
    }
    int cversion = cmp_str(cmd, (const char*)"version");
    if (cversion == 1) {
        terminal_print_string("KetOS 0.0.1");
    }
}

void shell_main() {
    terminal_print_string((const char*)"MAIN_KETOS:/> ");

    while(1) {
        __asm__("hlt");
        }
}

