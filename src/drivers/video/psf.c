/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */


#include <drivers/video/psf.h>
#include <stdint.h>
#include <stddef.h>
#include <drivers/video/framebuffer.h>

extern char _binary_src_common_default8x16_psf_start;
extern char _binary_src_common_default8x16_psf_end;

struct psf_font *font;
uint16_t *unicode;
void init_psf(){
	font = (struct psf_font*)&_binary_src_common_default8x16_psf_start;
	if (font->magic == 0) {
		unicode = NULL;
		return;
	}
}

void psf_render_char(char c, int x, int y, uint32_t fg, uint32_t bg){
	uint8_t *glyph = (uint8_t*)&_binary_src_common_default8x16_psf_start +
			4 + (c * font->char_size);
	for (int y2 = 0; y2 < font->char_size; y2++){
		uint8_t cur_byte = glyph[y2];
		for (int x2 = 0; x2 < 8; x2++){
			if ((cur_byte & (0x80 >> x2)) != 0) {
				fb_plot_pixel(x + x2, y + y2, fg);
			}
			else {
				fb_plot_pixel(x + x2, y + y2, bg);
			}
		}
	}
}