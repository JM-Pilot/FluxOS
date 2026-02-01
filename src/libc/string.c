#include <stddef.h>
#include <libc/string.h>
#include <stdint.h>
void *memset(void *dest, int val, size_t bytes){
	uint8_t *d = dest;
	while (bytes-- > 0)
		*d++ = val;
	return dest;
}