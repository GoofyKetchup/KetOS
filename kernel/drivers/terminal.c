#include "terminal.h"
#include "io.h"
#include <stdint.h>

#define TERMINAL_MEMORY 0xB8000

static uint16_t* terminal_buffer = (uint16_t*) TERMINAL_MEMORY;
static uint16_t cursor_pos = 0;

void terminal_set_cursor(uint16_t pos) {
    cursor_pos = pos;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t terminal_get_cursor() {
    uint16_t pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    return pos;
}

void terminal_clear() {
    for (int i = 0; i < TERMINAL_WIDTH * TERMINAL_HEIGHT; i++) {
        terminal_buffer[i] = (0x07 << 8) | ' ';
    }

    terminal_set_cursor(0);
}

void terminal_update_cursor() {
    cursor_pos = terminal_get_cursor();
    terminal_set_cursor(cursor_pos);
}

void terminal_put_char(char c) {

    if (c == '\n') {
        cursor_pos += TERMINAL_WIDTH - (cursor_pos % TERMINAL_WIDTH);
    } else {
        terminal_buffer[cursor_pos] = (0x07 << 8) | c;
        cursor_pos++;
    }

    if (cursor_pos >= TERMINAL_WIDTH * TERMINAL_HEIGHT) {
        terminal_scroll();
        cursor_pos -= TERMINAL_WIDTH;
    }

    terminal_set_cursor(cursor_pos);
}

void terminal_delete_char() {
    if (cursor_pos == 0) return;

    cursor_pos--;
    terminal_buffer[cursor_pos] = (0x07 << 8) | ' ';
    terminal_set_cursor(cursor_pos);
}

void terminal_init() {
    terminal_clear();
    terminal_set_cursor(0);
}

void terminal_scroll() {
    uint16_t* buffer = (uint16_t*) 0xB8000;

    for (int y = 1; y < TERMINAL_HEIGHT; y++) {
        for (int x = 0; x < TERMINAL_WIDTH; x++) {
            buffer[(y - 1) * TERMINAL_WIDTH + x] = buffer[y * TERMINAL_WIDTH + x];
        }
    }

    for (int x = 0; x < TERMINAL_WIDTH; x++) {
        buffer[(TERMINAL_HEIGHT - 1) * TERMINAL_WIDTH + x] = (0x07 << 8) | ' ';
    }
}