#include <kernel/cpu_hang.h>
#include <boot/requests.h>
#include <drivers/framebuffer.h>
#include <arch/x86_64/gdt/gdt.h>
#include <arch/x86_64/ints/idt.h>
void kernel_main(){
	asm volatile ("cli");
	check_requests();

	init_gdt();
	init_idt();

	init_framebuffer();

	asm volatile ("sti");
	fb_draw_square(10, 10, 50, 50, 0xFFFFFF);

	cpu_hang();
}