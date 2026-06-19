#include "io.h"
#include <stdint.h>

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND 0x43

#define PIT_FREQUENCY 1193182
#define HZ 1000

void timer_init() {
    uint16_t divisor = (uint16_t)(PIT_FREQUENCY / HZ);
    outb(PIT_COMMAND, 0x36);

    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF));
}