#include <kernel/cpu_hang.h>
#include <boot/requests.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/gdt/gdt.h>
#include <arch/x86_64/ints/idt.h>
#include <drivers/video/psf.h>
#include <drivers/video/console.h>
#include <mem/pmm.h>
void kernel_main(){
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
	
	cpu_hang();
}