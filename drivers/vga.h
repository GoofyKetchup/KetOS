#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_init();
void vga_put_char(char c);
void vga_clear();
void vga_set_cursor(uint16_t pos);
uint16_t vga_get_cursor();
void vga_update_cursor();
void vga_scroll();

#endif