#include <stdint.h>
#include <boot/limine.h>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

extern struct limine_framebuffer *framebuffer;
extern uint32_t *framebuffer_ptr;
void init_framebuffer();
void fb_plot_pixel(int x, int y, uint32_t color);
void fb_draw_square(int x, int y, int w, int h, uint32_t color);
#endif