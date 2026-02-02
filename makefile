CC = x86_64-elf-gcc
NASM = nasm -f elf64

SRC = src
BIN = bin
INC = inc
ISO_ROOT = iso_root

C_SRCS = $(shell find $(SRC) -iname "*.c")
C_OBJS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(C_SRCS))

ASM_SRCS = $(shell find $(SRC) -iname "*.asm")
ASM_OBJS = $(patsubst $(SRC)/%.asm, $(BIN)/%.o, $(ASM_SRCS))

FONT_OBJ = $(BIN)/common/default8x16.o
OBJS = $(C_OBJS) $(ASM_OBJS) $(FONT_OBJ)

C_FLAGS = -ffreestanding \
	-nostdlib \
	-O2 \
	-Wall \
	-Wextra \
	-g \
	-I$(INC) \
	-m64 \
	-mcmodel=kernel \
	-fno-pic \
	-fno-pie \
	-mno-red-zone \
	-std=gnu11 \
	-mno-sse \
	-mno-sse2 \
	-mno-mmx
LD_FLAGS = -ffreestanding \
	-nostdlib \
	-g \
	-static \
	-T $(SRC)/boot/linker.ld

OUTPUT = FluxOS

all: $(BIN)/$(OUTPUT).iso 

limine:
	if [ ! -d Limine ]; then \
		git clone https://codeberg.org/Limine/Limine.git --branch=v10.x-binary --depth=1; \
	fi
	mkdir -p $(ISO_ROOT)/Limine
	cp Limine/*.bin $(ISO_ROOT)/Limine/
	cp Limine/*.sys $(ISO_ROOT)/Limine/
$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/%.asm | $(BIN)
	mkdir -p $(dir $@)
	$(NASM) $< -o $@

$(FONT_OBJ): $(SRC)/common/default8x16.psf
	mkdir -p $(dir $@)
	objcopy -O elf64-x86-64 -B i386 -I binary $< $@

$(BIN)/$(OUTPUT).bin: $(OBJS)
	$(CC) $(LD_FLAGS) $^ -o $@

$(BIN)/$(OUTPUT).iso: $(BIN)/$(OUTPUT).bin limine
	cp $< $(ISO_ROOT)
	xorriso -as mkisofs -R -r -J -b Limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot Limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $(ISO_ROOT) -o $@
	./$(ISO_ROOT)/Limine/limine bios-install $@

$(BIN):
	mkdir -p $@
run: $(BIN)/$(OUTPUT).iso
	qemu-system-x86_64 -cdrom $< -bios $(ISO_ROOT)/EFI/OVMF.4m.fd -d int,cpu_reset -D $(BIN)/QEMU_LOG.txt -no-reboot -no-shutdown

clean:
	rm -rf $(BIN)
	rm -rf iso_root/FluxOS.bin