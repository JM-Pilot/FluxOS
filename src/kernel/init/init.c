/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <kernel/init/init.h>

void init_all(){
	asm volatile ("cli");
	
	check_requests();

	init_gdt();
	init_idt();
	

	init_framebuffer();
	init_psf();
	init_console();

	init_pmm();

	write_str("Finished Initializing\nWelcome to FluxOS!\n\n");

	pmm_print_usable_ram();
	
	asm volatile ("sti");
}