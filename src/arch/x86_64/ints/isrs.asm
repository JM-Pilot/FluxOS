[BITS 64]
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
	xor rax, rax
	push rax
	push 0
	call exception_handler
	iretq
isr1:
	push 1
	call exception_handler
	iretq
isr2:
	push 2
	call exception_handler
	iretq
isr3:
	push 3
	call exception_handler
	iretq
isr4:
	push 4
	call exception_handler
	iretq
isr5:
	push 5
	call exception_handler
	iretq
isr6:
	push 6
	call exception_handler
	iretq
isr7:
	push 7
	call exception_handler
	iretq
isr8:
	push 8
	call exception_handler
	iretq
isr9:
	push 9
	call exception_handler
	iretq
isr10:
	call exception_handler
	iretq
isr11:
	call exception_handler
	iretq
isr12:
	call exception_handler
	iretq
isr13:
	call exception_handler
	iretq
isr14:
	call exception_handler
	iretq
isr15:
	call exception_handler
	iretq
isr16:
	push 16 
	call exception_handler
	iretq
isr17:
	call exception_handler
	iretq
isr18:
	push 18
	call exception_handler
	iretq
isr19:
	push 19
	call exception_handler
	iretq
isr20:
	push 20
	call exception_handler
	iretq
isr21:
	call exception_handler
	iretq
isr22:
	call exception_handler
	iretq
isr23:
	call exception_handler
	iretq
isr24:
	call exception_handler
	iretq
isr25:
	call exception_handler
	iretq
isr26:
	call exception_handler
	iretq
isr27:
	call exception_handler
	iretq
isr28:
	call exception_handler
	iretq
isr29:
	call exception_handler
	iretq
isr30:
	push 30
	call exception_handler
	iretq
isr31:
	call exception_handler
	iretq

extern print_error
exception_handler:
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsi
	push rdi
	push rbp
	push rdx
	push rcx
	push rbx
	push rax
	mov rdi, rsp
	call print_error
	; Hang (NO RETURN, yes very stupid move - JM-Pilot)