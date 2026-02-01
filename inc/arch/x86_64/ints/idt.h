#include <stdint.h>
#ifndef IDT_H
#define IDT_H
void idt_set_entry(int num, uint64_t offset, uint8_t flags);
void init_idt();

#endif