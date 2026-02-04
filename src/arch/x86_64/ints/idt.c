/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <arch/x86_64/ints/idt.h>
#include <stdint.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <kernel/cpu_hang.h>
#include <arch/x86_64/ints/isr.h>

extern void* interruptTable[256];

struct idt_entry {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t  ist;
	uint8_t  type_attributes;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t reserved;
}__attribute__((packed));

struct idtr {
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));

struct interrupt_frame {
    uint64_t alignment_padding;
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    uint64_t intNo;
    uint64_t errorCode;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
}__attribute__((packed));

static char const* faultMessages[32] = {
    "Division Exception",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Detected Overflow",
    "Out Of Bounds",
    "Invalid OpCode",
    "No CoProcessor",
    "Double Fault",
    "CoProcessor Segment Overrun",
    "Bad Tss",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "CoProcessor Fault",
    "Alignment Check",
    "Machine Check",
    "Simd Floating Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Hypervisor Injection Exception",
    "Vmm Communication Exception",
    "Security Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

static struct idt_entry idt[256];

void idt_set_entry(int num, uint64_t offset, uint8_t flags){
	idt[num].offset_low = offset & 0xFFFF;
	idt[num].offset_mid = (offset >> 16) & 0xFFFF;
	idt[num].offset_high = (offset >> 32) & 0xFFFFFFFF;
	idt[num].selector = 0x08;
	idt[num].ist = 0;
	idt[num].reserved = 0;
	idt[num].type_attributes = flags;
}

void init_idt(){
	struct idtr idt_ptr;
	idt_ptr.size = sizeof(idt) - 1;
	idt_ptr.offset = (uint64_t)&idt;

	memset(idt, 0, sizeof(idt));

	for (int i = 0; i < 256; i++){
		idt_set_entry(i, (uint64_t)interruptTable[i], 0x8e);
	}

	__asm__ volatile( "lidt %0"
			:
			: "m" (idt_ptr)
			: "memory");
}


// this function gets called on interrupt
void handleInterruptAsm(struct interrupt_frame *f) {
	if (f->intNo < 32) {
		printf("\nGot called with interrupt %s.\n", faultMessages[f->intNo]);
		printf("--------------------------------------\n");
		printf("REGISTER TRACE:\n");
		printf("RAX=%x; RBX=%x; RCX=%x;\nRDX=%x; RSI=%x; RDI=%x;\nRIP=%x;  CS=%x; RSP=%x;\nError code: %d.\nHalting.", f->rax, f->rbx, f->rcx, f->rdx, f->rsi, f->rdi, f->rip, f->cs, f->rsp, f->errorCode);
		cpu_hang();
	}
}