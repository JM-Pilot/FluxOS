/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */


#include <stdint.h>
#include <boot/limine.h>
#include <boot/requests.h>
#include <drivers/video/framebuffer.h>

struct limine_framebuffer *framebuffer;
uint32_t *framebuffer_ptr;

void init_framebuffer(){
	framebuffer = framebuffer_request.response->framebuffers[0];
	framebuffer_ptr = framebuffer->address;
}
void fb_plot_pixel(int x, int y, uint32_t color){
	framebuffer_ptr[y * framebuffer->width + x] = color;
}

void fb_draw_square(int x, int y, int w, int h, uint32_t color){
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			fb_plot_pixel(x + j, y + i, color);
}