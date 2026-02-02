#include <boot/limine.h>

#ifndef REQUESTS_H
#define REQUESTS_H

extern volatile uint64_t limine_base_revision[];
extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_memmap_request memmap_request;
void check_requests();
#endif