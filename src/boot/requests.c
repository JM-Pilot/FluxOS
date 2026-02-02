#include <boot/requests.h>
#include <stdbool.h>
#include <boot/limine.h>
#include <kernel/cpu_hang.h>
#include <stddef.h>

__attribute__((used, section(".limine_requests")))
volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0,
};

void check_requests(){
	if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) cpu_hang();
	if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) cpu_hang();
	if (memmap_request.response == NULL || memmap_request.response->entry_count < 1) cpu_hang();
}