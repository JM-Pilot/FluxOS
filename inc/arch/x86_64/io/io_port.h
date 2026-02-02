#include <stdint.h>
#ifndef IO_PORT_H
#define IO_PORT_H

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait();
#endif