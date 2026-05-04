#include "../drivers/vga.h"
#include "vga_utils.h"

void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_put_char(str[i]);
    }
}