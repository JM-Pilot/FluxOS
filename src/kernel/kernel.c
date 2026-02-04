#include <kernel/cpu_hang.h>
#include <kernel/init/init.h>
void kernel_main(){
	init_all();
	// asm volatile ("int $0x00");
	cpu_hang();
}