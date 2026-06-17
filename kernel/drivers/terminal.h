#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25

void terminal_init();
void terminal_put_char(char c);
void terminal_delete_char();
void terminal_clear();
void terminal_set_cursor(uint16_t pos);
uint16_t terminal_get_cursor();
void terminal_update_cursor();
void terminal_scroll();

#endif