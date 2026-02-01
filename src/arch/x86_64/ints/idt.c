#include <arch/x86_64/ints/idt.h>
#include <stdint.h>
#include <libc/string.h>
#include <arch/x86_64/ints/isr.h>
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

static struct idt_entry idt[256];
static struct idtr idt_ptr;
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
	idt_ptr.size = sizeof(idt) - 1;
	idt_ptr.offset = (uint64_t)&idt;

	memset(idt, 0, sizeof(idt));
	init_isr();
	
	__asm__ volatile( "lidt %0"
			:
			: "m" (idt_ptr)
			: "memory");
}