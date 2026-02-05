/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <mem/pmm.h>
#include <boot/requests.h>
#include <stdint.h>
#include <boot/limine.h>
#include <drivers/video/console.h>
#include <libc/stdio.h>
#include <libc/string.h>

uint8_t* bmap_virt_addr = 0;
uint64_t bmap_in_bytes = 0;
uint64_t usable_ram = 0;

uint64_t hhdm;

void pmm_print_usable_ram(){
	/* I am smart */
	printf("Usable Ram: %d Bytes, %d Kilobytes\n", usable_ram, usable_ram / 1024);
	printf("            %d Megabytes,    %d Gigabytes\n", usable_ram / 1024 / 1024, usable_ram / 1024 / 1024 / 1024);
}

void bitmap_set(int page) {
    int byte = page / 8;
    int bit = page % 8;
    bmap_virt_addr[byte] |= (1 << bit);
}

void bitmap_clear(int page) {
    int byte = page / 8;
    int bit = page % 8;
    bmap_virt_addr[byte] &= ~(1 << bit);
}

uint64_t pmm_alloc() {
    for (uint64_t i = 0; i < bmap_in_bytes; i++) {
        if (bmap_virt_addr[i] == 0xFF) {
            continue;
        }
        for (int o = 0; o < 8; o++) {
            int bit = (bmap_virt_addr[i] >> o) & 1;
            if (bit == 0) {
                int page = (i * 8) + o;
                bitmap_set(page);
                uint64_t phys_addr = page * 4096;
                return phys_addr;
            }
        }
    }
    return 0;
}

void pmm_free(void* addr) {
    uint64_t phys_addr = (uint64_t)addr - hhdm;
    int page_index = phys_addr / 4096;
    bitmap_clear(page_index);
}

void init_pmm() {
    hhdm = hhdm_rq.response->offset;
    uint64_t bmap_phys_addr = 0;
    uint64_t count = memmap_request.response->entry_count;
    uint64_t highest_address = 0;
    for (uint64_t i = 0; i < count; i++) {
    
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE || entry->type == LIMINE_MEMMAP_EXECUTABLE_AND_MODULES || entry->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
            uint64_t end_of_chunk = entry->base + entry->length;
	    usable_ram += entry->length;

            if (end_of_chunk > highest_address) {
                highest_address = end_of_chunk;
            }
        } 
    }
    bmap_in_bytes = highest_address / 4096;
    bmap_in_bytes = (bmap_in_bytes + 7) / 8;

    for (uint64_t i = 0; i < count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE && entry->length > bmap_in_bytes) {
            bmap_phys_addr = entry->base;
            break;
        } 
    }
    
    bmap_virt_addr = (uint8_t*)(bmap_phys_addr + hhdm);
    memset(bmap_virt_addr, 0xFF, bmap_in_bytes);
    for (uint64_t i = 0; i < count; i++) {
    
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE) {
            int start_page = entry->base / 4096;
            int times = entry->length / 4096;
            for (int o = 0; o < times; o++) {
                bitmap_clear(start_page + o);
            }
        } 
    }
    int bitmap_page = bmap_phys_addr / 4096;
    int bitmap_in_pages = (bmap_in_bytes + 4095) / 4096;
    for (int o = 0; o < bitmap_in_pages; o++) {
        bitmap_set(bitmap_page + o);
    }
    bitmap_set(0);
}