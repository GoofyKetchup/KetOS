#include "../drivers/terminal.h"
#include "console.h"

void terminal_print_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        terminal_put_char(str[i]);
    }
}