#include <drivers/video/console.h>
#include <drivers/video/psf.h>
#include <drivers/video/framebuffer.h>
#include <stdint.h>
int console_x;
int console_y;
uint32_t console_def_fg;
uint32_t console_def_bg;

void init_console(){
	console_x = 0, console_y = 0;
	console_def_fg = 0xFFFFFF;
	console_def_bg = 0x000000;
}

void insert_newline(){
	console_y += 16;
	console_x = 0;
}
void write_char(char c){
	if (c == '\n'){
		insert_newline();
		return;
	}
	if (console_x + 16 >= framebuffer->width){
		insert_newline();
	}
	psf_render_char(c, console_x, console_y, console_def_fg, console_def_bg);
	console_x += 9;
}

void write_str(const char *s){
	for (int i = 0; s[i] != '\0'; i++)
		write_char(s[i]);
}
