#include <stdint.h>
#include "idt.h"
#include "..\drivers\io.h"
#include "..\drivers\terminal.h"
#include "..\lib\ASCII.H"
#include "..\lib\console.h"
#include "..\..\os\cli\shell.h"

// PIC Ports
#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

#define INPUT_BUFFER_SIZE 512

static char input_buffer[INPUT_BUFFER_SIZE];
static int input_len = 0;

typedef struct regs {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no;
    uint32_t err_code;
} regs_t;

typedef struct __attribute__((packed)){
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} idt_entry_t ;

typedef struct __attribute__((packed)){
    uint16_t limit;
    uint32_t base;
} idt_ptr_t ;

extern void isr_common_stub();
extern void idt_load(idt_ptr_t* ptr);
extern void irq1_keyboard_handler();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr33();

idt_entry_t idt[256];

idt_ptr_t idt_ptr = {
    .limit = sizeof(idt) - 1,
    .base = (uint32_t)&idt
};

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

void remap_pic() {
    outb(PIC_MASTER_CMD, 0x11);
    outb(PIC_SLAVE_CMD, 0x11);

    outb(PIC_MASTER_DATA, 0x20);
    outb(PIC_SLAVE_DATA, 0x28);

    outb(PIC_MASTER_DATA, 0x04);
    outb(PIC_SLAVE_DATA, 0x02);

    outb(PIC_MASTER_DATA, 0x01);
    outb(PIC_SLAVE_DATA, 0x01);
    
    outb(PIC_MASTER_DATA, 0xFD);
    outb(PIC_SLAVE_DATA, 0xFF);
}

void idt_init() {
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, (uint32_t)isr_common_stub, 0x08, 0x8E);
    }
    
    idt_set_gate(0,  (uint32_t)isr0,  0x08, 0x8E);
    idt_set_gate(1,  (uint32_t)isr1,  0x08, 0x8E);
    idt_set_gate(2,  (uint32_t)isr2,  0x08, 0x8E);
    idt_set_gate(3,  (uint32_t)isr3,  0x08, 0x8E);
    idt_set_gate(4,  (uint32_t)isr4,  0x08, 0x8E);
    idt_set_gate(5,  (uint32_t)isr5,  0x08, 0x8E);
    idt_set_gate(6,  (uint32_t)isr6,  0x08, 0x8E);
    idt_set_gate(7,  (uint32_t)isr7,  0x08, 0x8E);
    idt_set_gate(8,  (uint32_t)isr8,  0x08, 0x8E);
    idt_set_gate(9,  (uint32_t)isr9,  0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8E);

    remap_pic();

    idt_load(&idt_ptr);
}

extern void shell_print_prompt();
extern void execute_command(const char* cmd);

void panic(const char* msg);
void irq1_keyboard_c();

void isr_handler(regs_t* r) {
    switch(r->int_no) {
        case 0: panic((const char*)"DIVISION BY ZERO"); break;
        case 1: terminal_print_string((const char*)"Debug not Accesible on this KetOS Edition.\n"); return;
        case 2: panic((const char*)"NON MASKABLE INTERRUPT"); break;
        case 3: panic((const char*)"Breakpoint Reached"); break;
        case 4: panic((const char*)"OVERFLOW"); break;
        case 5: terminal_print_string((const char*)"Bound Range Exceeded.\n"); return;
        case 6: terminal_print_string((const char*)"Invalid Opcode.\n"); return;
        case 7: panic((const char*)"DEVICE NOT AVAILABLE"); break;
        case 8: panic((const char*)"CRITIC DOUBLE FAULT"); break;
        case 9: panic((const char*)"COPROCESSOR SEGMENT OVERRUN OR RESERVED"); break;
        case 10: panic((const char*)"INVALID TSS SEGMENT"); break;
        case 11: panic((const char*)"SEGMENT NOT PRESENT"); break;
        case 12: __asm__ volatile("cli"); __asm__ volatile("hlt"); break;
        case 13: panic((const char*)"GENERAL PROTECTION FAULT."); break;
        case 14: panic((const char*)"PAGE FAULT"); break;
        case 15: terminal_print_string((const char*)"Reserved 15.\n"); return;
        case 16: terminal_print_string((const char*)"x87 Floating point exception.\n"); return;
        case 17: panic((const char*)"ALIGMENT CHECK"); break;
        case 18: panic((const char*)"MACHINE CHECK"); break;
        case 19: terminal_print_string((const char*)"SIMD floating point exception.\n"); return;
        case 20: terminal_print_string((const char*)"Virtualization exception.\n"); return;
        case 21: panic((const char*)"CONTROL PROTECTION EXCEPTION"); break;
        case 22: terminal_print_string((const char*)"Reserved 22.\n"); return;
        case 23: terminal_print_string((const char*)"Reserved 23.\n"); return;
        case 24: terminal_print_string((const char*)"Reserved 24.\n"); return;
        case 25: terminal_print_string((const char*)"Reserved 25.\n"); return;
        case 26: terminal_print_string((const char*)"Reserved 26.\n"); return;
        case 27: terminal_print_string((const char*)"Reserved 27.\n"); return;
        case 28: terminal_print_string((const char*)"Hypervisor injection exception.\n"); return;
        case 29: terminal_print_string((const char*)"VMM communication exception.\n"); return;
        case 30: panic((const char*)"SECURITY EXCEPTION"); break;
        case 31: terminal_print_string((const char*)"Reserved 31.\n"); return;
        case 33:
            irq1_keyboard_c();
            outb(0x20, 0x20);
            return;
        default:
            if (r->int_no >= 0x20 && r->int_no <= 0x2F) {
                if (r-> int_no >= 0x28)
                    outb(0xA0, 0x20);
                outb(0x20, 0x20);
            }
            return;
    }
}

void panic(const char* msg) {
    terminal_print_string("\n [KERNEL PANIC] ");
    terminal_print_string(msg);
    terminal_print_string("\n");
    __asm__ volatile("cli");
    for(;;) __asm__ volatile("hlt");
}

void irq1_keyboard_c() {
    uint8_t scancode = inb(0x60);
    if (scancode >= 0x80) return;

    char c = scancode_to_ascii(scancode);
    if (c == 0) return;

    if (c == '\b') {
        if (input_len > 0) {
            input_len--;
            terminal_delete_char();
        }
        return;
    }

    if (c == '\n') {
        terminal_put_char('\n');
        execute_command(input_buffer);
        input_buffer[0] = '\0';
        input_len = 0;
        terminal_print_string((const char*)"\nSYS_USER@KETOS - $ ");
        return;
    }

    if (input_len < INPUT_BUFFER_SIZE - 1) {
        input_buffer[input_len++] = c;
        input_buffer[input_len] = '\0';
        terminal_put_char(c);
    }
}