#include <stdint.h>
#include "..\lib\vga_utils.h"

extern void isr0();
extern void isr_default();

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void set_idt_gate(int n, uint32_t handler, struct idt_entry *idt) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void isr_handler(int interrupt) {
    switch(interrupt) {
        case 0:
            vga_print("KERNEL PANIC: DIVISION BY ZERO\n");
            while(1) {
                asm volatile("hlt");
            }
            break;
        default:
            vga_print("KERNEL PANIC: UNKNOWN INTERRUPTION\n");
            while(1) {
                __asm__ volatile("hlt");
            }
            break;
    }
}

void idt_init() {
    static struct idt_entry idt[256];
    struct idtr idt_reg;

    for (int i = 0; i < 256; i++) {
        set_idt_gate(i, (uint32_t) isr_default, idt);
    }

    set_idt_gate(0, (uint32_t) isr0, idt);

    idt_reg.limit = sizeof(idt) - 1;
    idt_reg.base = (uint32_t)&idt;

    __asm__ __volatile__("lidt %0" : : "m"(idt_reg));
}