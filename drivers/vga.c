#include "vga.h"
#include "../lib/port_utils.c"

#define VGA_MEMORY 0xB8000

static uint16_t* vga_buffer = (uint16_t*) VGA_MEMORY;
static uint16_t cursor_pos = 0;

void vga_set_cursor(uint16_t pos) {
    cursor_pos = pos;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t vga_get_cursor() {
    uint16_t pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    return pos;
}

void vga_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = (0x07 << 8) | ' ';
    }

    vga_set_cursor(0);
}

void vga_update_cursor() {
    cursor_pos = vga_get_cursor();
    vga_set_cursor(cursor_pos);
}

void vga_put_char(char c) {

    vga_update_cursor();

    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else {
        vga_buffer[cursor_pos] = (0x07 << 8) | c;
        cursor_pos++;
    }

    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT) {
        vga_scroll();
        cursor_pos -= VGA_WIDTH;
    }

    vga_set_cursor(cursor_pos);
}

void vga_init() {
    vga_clear();
    vga_set_cursor(0);
}

void vga_scroll() {
    uint16_t* buffer = (uint16_t*) 0xB8000;

    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            buffer[(y - 1) * VGA_WIDTH + x] = buffer[y * VGA_WIDTH + x];
        }
    }

    for (int x = 0; x < VGA_WIDTH; x++) {
        buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (0x07 << 8) | ' ';
    }
}