#include <stdint.h>
#include <arch/x86_64/ints/isr.h>
#include <arch/x86_64/ints/idt.h>
#include <drivers/video/console.h>
#include <kernel/cpu_hang.h>
#include <libc/stdio.h>
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

uint64_t isr_table[32] = {
    (uint64_t)isr0,  (uint64_t)isr1,  (uint64_t)isr2,  (uint64_t)isr3,
    (uint64_t)isr4,  (uint64_t)isr5,  (uint64_t)isr6,  (uint64_t)isr7,
    (uint64_t)isr8,  (uint64_t)isr9,  (uint64_t)isr10, (uint64_t)isr11,
    (uint64_t)isr12, (uint64_t)isr13, (uint64_t)isr14, (uint64_t)isr15,
    (uint64_t)isr16, (uint64_t)isr17, (uint64_t)isr18, (uint64_t)isr19,
    (uint64_t)isr20, (uint64_t)isr21, (uint64_t)isr22, (uint64_t)isr23,
    (uint64_t)isr24, (uint64_t)isr25, (uint64_t)isr26, (uint64_t)isr27,
    (uint64_t)isr28, (uint64_t)isr29, (uint64_t)isr30, (uint64_t)isr31
};
const char *error_codes[32] = {
    "Divide Error (DIV BY ZERO)",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x86 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};
__attribute__((noreturn))
void print_error(struct registers *reg){
    write_error("\n[ERR] EXCEPTION REACHED!\n");
    console_def_fg = 0xFF0000;
    console_def_bg = 0x0000FF;

    printf("Error Code: %s\n", error_codes[reg->vector]);

    printf("RIP: %x\n", reg->rip);
    printf("CS: %x\n", reg->cs);
    printf("RFLAGS: %x\n", reg->rflags);

    printf("RAX: %x\n", reg->rax);
    printf("RBX: %x\n", reg->rbx);
    printf("RCX: %x\n", reg->rcx);
    printf("RDX: %x\n", reg->rdx);

    printf("RSI: %x\n", reg->rsi);
    printf("RDI: %x\n", reg->rdi);
    printf("RBP: %x\n", reg->rbp);
    printf("RSP: %x\n", reg->rsp);

    printf("R8 : %x\n", reg->r8);
    printf("R9 : %x\n", reg->r9);
    printf("R10: %x\n", reg->r10);
    printf("R11: %x\n", reg->r11);

    printf("R12: %x\n", reg->r12);
    printf("R13: %x\n", reg->r13);
    printf("R14: %x\n", reg->r14);
    printf("R15: %x\n", reg->r15);

    write_error("[ERR] HALTING CPU (UNRECOVERABLE)");
    cpu_hang();
    for (;;);
}
void init_isr(){
	for (int i = 0; i < 32; i++){
		idt_set_entry(i, isr_table[i], 0x8e);
	}
}