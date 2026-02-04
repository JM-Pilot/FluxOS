/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <arch/x86_64/io/io_port.h>
#include <stdint.h>
void outb(uint16_t port, uint8_t val){
	asm volatile ("outb %0, %1" 
			:
			: "a" (val), "Nd" (port)
			:);
}

uint8_t inb(uint16_t port){
	uint8_t ret;
	asm volatile ("inb %1, %0"
			: "=a" (ret)
			: "Nd" (port)
			: "memory");
	return ret;
}

void io_wait(){
    	outb(0x80, 0);
}