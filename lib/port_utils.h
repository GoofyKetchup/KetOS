#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val);
static inline uint8_t inb(uint16_t port);

#endif