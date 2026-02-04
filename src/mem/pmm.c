/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

/* Some parts of these are not yet verified by me (JM-Pilot), because this allocator was made by a friend of mine (he is very pro) */
/* no worries bro, i verified it, its shit */

#include <mem/pmm.h>
#include <boot/requests.h>
#include <stdint.h>
#include <boot/limine.h>
#include <drivers/video/console.h>
#include <libc/stdio.h>
#define PAGE_SIZE 4096

uint64_t usable_ram;
uint64_t number_of_pages;
uint64_t bitmap_size;
uint8_t *bitmap = (uint8_t*)0xFFFFFFFF80208000;
void init_pmm(){
	/* Someone help me here idk what im doing */
	/* you are looking through the limine memory map and checking if the entry is usable, if not, skip it. if its usable, add the size of the entry to the usable ram */
	for (uint64_t i = 0; i < memmap_request.response->entry_count; i++){
		struct limine_memmap_entry *entry = memmap_request.response->entries[i];
		if (entry->type == LIMINE_MEMMAP_USABLE){
			usable_ram += entry->length;
		}
	}
	number_of_pages = usable_ram / PAGE_SIZE;
	bitmap_size = (number_of_pages + 7) / 8;
}

void pmm_print_usable_ram(){
	/* I am smart */
	printf("Usable Ram: %d Bytes, %d Kilobytes\n", usable_ram, usable_ram / 1024);
	printf("            %d Megabytes,    %d Gigabytes\n", usable_ram / 1024 / 1024, usable_ram / 1024 / 1024 / 1024);
}

uint64_t pmm_allocate(){
	for (uint64_t byte = 0; byte < bitmap_size; byte++){
		if (bitmap[byte] != 0xFF) {
			for (uint8_t bit = 0; bit < 8; bit++) {
				if (!(bitmap[byte] & (1 << bit))) {
					bitmap[byte] |= 1 << bit;
					return (byte * 8 + bit) * PAGE_SIZE;
				}
			}
		}
	}
	return 0;
}

void pmm_free(uint64_t phys_addr) {
	uint64_t frame_index = phys_addr / PAGE_SIZE;
	bitmap[frame_index / 8] &= ~(1 << (frame_index % 8));
}
