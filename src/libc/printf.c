/*
 *          Flux Kernel
 * Copyright (c) jm-pilot, 2025-2026
 * Copytight (c) sakettor, 2025-2026
 */

#include <libc/stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <drivers/video/console.h>
void printf(const char *fmt, ...){
	uint64_t fi = 0;
	va_list arg;
	va_start (arg, fmt);
	for (int i = 0 ; fmt[i] != '\0'; i++){
		if (fmt[i] == '%'){
			switch (fmt[i + 1]){
				case 'd':
					fi = va_arg(arg,long);
					write_int64(fi);
					i++;
					break;
				case 'c':
					fi = va_arg(arg,int);
					write_char(fi);
					i++;
					break;
				case 's':
					char *si;
					si = va_arg(arg,char *);
					write_str(si);
					i++;
					break;
				case 'x':
					fi = va_arg(arg,uint64_t);
					write_hex(fi);
					i++;
					break;
				default:
					i++;
					break;
			}
		} else {
			write_char(fmt[i]);
		}
	}
	va_end(arg);
}