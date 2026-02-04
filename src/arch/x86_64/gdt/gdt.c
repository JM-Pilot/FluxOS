/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <arch/x86_64/gdt/gdt.h>
#include <stdint.h>

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__((packed));

struct gdtr {
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));

struct gdtr gdt_ptr;

extern void gdt_flush();

void set_entry(struct gdt_entry *gdt_table, uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt_table[num].base_low = (base & 0xFFFF);
	gdt_table[num].base_middle = (base >> 16) & 0xFF;
	gdt_table[num].base_high = (base >> 24) & 0xFF;

	gdt_table[num].limit_low = (limit & 0xFFFF);
	gdt_table[num].granularity = (limit >> 16) & 0x0F;

	gdt_table[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
	gdt_table[num].access = access;
}

struct gdt_entry gdt[5];

void init_gdt(){
	gdt_ptr.size = (sizeof(struct gdt_entry) * 5) - 1;
	gdt_ptr.offset = (uint64_t)&gdt;

	set_entry(gdt, 0, 0, 0, 0, 0);
	set_entry(gdt, 1, 0, 0xFFFFF, 0x9A, 0xAF); /* Kernel Code */
	set_entry(gdt, 2, 0, 0xFFFFF, 0x92, 0xCF); /* Kernel Data */
	set_entry(gdt, 3, 0, 0xFFFFF, 0xF2, 0xCF); /* User Code */
	set_entry(gdt, 4, 0, 0xFFFFF, 0xFA, 0xAF); /* User Data */
	
	gdt_flush();
}