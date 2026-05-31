#include <stdint.h>
#include "..\..\kernel\lib\console.h"
#include "..\..\kernel\lib\string.h"
#include "..\..\kernel\core\idt.h"

void execute_command(const char* cmd) {
    int ping = cmp_str(cmd, (const char*)"ping");
    if (ping == 1) {
        terminal_print_string("Pong.");
    }
    int version = cmp_str(cmd, (const char*)"version");
    if (version == 1) {
        terminal_print_string("KetOS 0.1.2");
    }
}

void shell_main() {
    terminal_print_string((const char*)"SYS_USER@KETOS - $ ");

    while(1) {
        __asm__("hlt");
        }
}

