#define SC(sc, ascii) case sc: return ascii;
#include "ASCII.H"

char scancode_to_ascii(uint8_t scancode) {
    switch (scancode) {
        SC(0x02, '1') SC(0x03, '2') SC(0x04, '3')
        SC(0x05, '4') SC(0x06, '5') SC(0x07, '6')
        SC(0x08, '7') SC(0x09, '8') SC(0x0A, '9')
        SC(0x0B, '0') SC(0x0E, '\b')

        SC(0x10, 'a') SC(0x11, 'z') SC(0x12, 'e')
        SC(0x13, 'r') SC(0x14, 't') SC(0x15, 'y')
        SC(0x16, 'u') SC(0x17, 'i') SC(0x18, 'o')
        SC(0x19, 'p')

        SC(0x1E, 'q') SC(0x1F, 's') SC(0x20, 'd')
        SC(0x21, 'f') SC(0x22, 'g') SC(0x23, 'h')
        SC(0x24, 'j') SC(0x25, 'k') SC(0x26, 'l')
        SC(0x27, 'm')

        SC(0x2C, 'w') SC(0x2D, 'x') SC(0x2E, 'c')
        SC(0x2F, 'v') SC(0x30, 'b') SC(0x31, 'n')
        SC(0x32, ',') SC(0x33, ';') SC(0x34, ':')
        SC(0x35, '!')

        SC(0x39, ' ')
        SC(0x1C, '\n')

        default: return 0;
    }
}