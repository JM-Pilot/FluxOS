#include <stdint.h>
#ifndef CONSOLE_H
#define CONSOLE_H

extern int console_x;
extern int console_y;
extern uint32_t console_def_fg;
extern uint32_t console_def_bg;
void init_console();
void write_char(char c);
void write_str(const char *c);
void write_error(const char *msg);
void write_int(int i);
void write_int64(long i);
void write_hex(uint64_t h);
#endif