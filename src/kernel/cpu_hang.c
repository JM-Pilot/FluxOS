#include <kernel/cpu_hang.h>

void cpu_hang(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}