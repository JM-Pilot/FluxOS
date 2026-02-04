/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <kernel/cpu_hang.h>

void cpu_hang(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}