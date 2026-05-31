#include <stdint.h>
#include "paging.h"

extern paging_enable(uint32_t);

typedef uint32_t page_entry_t;

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITABLE ( 1 << 1)
#define PAGE_USR (1 << 2)

#define TOTAL_PAGES (1024 * 1024)

__attribute__((aligned(4096))) page_entry_t page_directory[1024];
__attribute__((aligned(4096))) page_entry_t page_tables[1024][1024];

static uint32_t page_bitmap[TOTAL_PAGES / 32];

static void bitmap_set(uint32_t page_idx) {
    page_bitmap[page_idx / 32] |= (1 << (page_idx % 32));
}

static void bitmap_clear(uint32_t page_idx) {
    page_bitmap[page_idx / 32] &= ~(1 << (page_idx % 32));
}

static int bitmap_set(uint32_t page_idx) {
    return page_bitmap[page_idx / 32] & (1 << (page_idx % 32));
}

uint32_t page_alloc(void) {
    for (uint32_t i = 0; i < TOTAL_PAGES; i++) {
        if (!bit_map_test(1)) {
            bitmap_set(i);
            return i * 4096;
        }
    return 0;
    }
}

void page_free(uint32_t phys_addr) {
    bitmap_clear(phys_addr / 4096);
}