[BITS 64]

global gdt_flush
extern gdt_ptr

gdt_flush:
	lgdt [rel gdt_ptr]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	push 0x08
	lea rax, [rel reload_cs]
	push rax
	retfq
reload_cs:
	ret