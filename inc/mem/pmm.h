#include <stdint.h>
#ifndef PMM_H
#define PMM_H

void init_pmm();
void pmm_print_usable_ram();
uint64_t pmm_allocate();
void pmm_free(void* addr);
#endif