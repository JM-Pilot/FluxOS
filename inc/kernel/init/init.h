#include <boot/requests.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/gdt/gdt.h>
#include <arch/x86_64/ints/idt.h>
#include <drivers/video/psf.h>
#include <drivers/video/console.h>
#include <mem/pmm.h>
#include <libc/stdio.h>

#ifndef INIT_H
#define INIT_H

void init_all();
#endif