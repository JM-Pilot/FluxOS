#include <kernel/init/init.h>

void init_all(){
	asm volatile ("cli");
	
	check_requests();

	init_gdt();
	init_idt();
	
	init_pmm();

	init_framebuffer();
	init_psf();
	init_console();

	write_str("Finished Initializing\nWelcome to FluxOS!\n\n");

	pmm_print_usable_ram();
	
	asm volatile ("sti");
}