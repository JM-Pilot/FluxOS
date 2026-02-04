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
	if ((uint64_t)console_x + 16 >= framebuffer->width){
		insert_newline();
	}
	psf_render_char(c, console_x, console_y, console_def_fg, console_def_bg);
	console_x += 8;
}

void write_str(const char *s){
	for (int i = 0; s[i] != '\0'; i++)
		write_char(s[i]);
}

void write_error(const char *msg){
	console_def_fg = 0xFF0000;
	console_def_bg = 0x0000FF;
	write_str(msg);
	console_def_bg = 0x000000;
	console_def_fg = 0xFFFFFF;
}
void write_int(int i){
	int totl_num[256];
	int ptr = 0;

	if (i < 0) {
		write_char('-');
		i = -i;
	} 
	if (i == 0) {
		write_char('0');
		return;
	}   
    	while (i != 0) {
		totl_num[ptr++] = i % 10;
		i = i / 10;
    	}
	while (ptr-- != 0){
		write_char('0' + totl_num[ptr]);
	}
}
void write_hex(uint64_t h){
	const char* hex_vals = "0123456789ABCDEF";
	write_str("0x");
	for (int i = 60; i >= 0; i -= 4)
       		write_char(hex_vals[(h >> i) & 0xF]);
}

void write_int64(long i){
	int totl_num[256];
	int ptr = 0;

	if (i < 0) {
		write_char('-');
		i = -i;
	} 
	if (i == 0) {
		write_char('0');
		return;
	}   
    	while (i != 0) {
		totl_num[ptr++] = i % 10;
		i = i / 10;
    	}
	while (ptr-- != 0){
		write_char('0' + totl_num[ptr]);
	}
}