# Makefile para build do kernel knl64
# Requer: x86_64-linux-gnu-gcc, nasm, grub-mkrescue, xorriso

# Toolchain
CC := x86_64-linux-gnu-gcc
AS := nasm
LD := x86_64-linux-gnu-ld

# Flags
CFLAGS := -ffreestanding -O2 -Wall -Wextra -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2
ASFLAGS := -f elf64
LDFLAGS := -n -T linker.ld -nostdlib

# Diretórios
SRC_DIR := ../src
BUILD_DIR := .
ISO_DIR := $(BUILD_DIR)/isodir

# Arquivos fonte
ASM_SOURCES := $(SRC_DIR)/boot/boot.asm
C_SOURCES := $(SRC_DIR)/main.c $(SRC_DIR)/boot/boot.c $(SRC_DIR)/boot/multiboot2.c $(SRC_DIR)/memory/memory.c

# Objetos
ASM_OBJECTS := $(SRC_DIR)/boot/boot.o
C_OBJECTS := $(SRC_DIR)/main.o $(SRC_DIR)/boot/boot_c.o $(SRC_DIR)/boot/multiboot2.o $(SRC_DIR)/memory/memory.o
OBJECTS := $(ASM_OBJECTS) $(C_OBJECTS)

# Alvos
.PHONY: all clean run iso

all: kernel.elf

# Compilar kernel
kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel compilado: kernel.elf"

# Regra para assembly
$(SRC_DIR)/boot/boot.o: $(SRC_DIR)/boot/boot.asm
	$(AS) $(ASFLAGS) $< -o $@

# Regra para arquivos C
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/boot/boot_c.o: $(SRC_DIR)/boot/boot.c
	$(CC) $(CFLAGS) -c $< -o $@

# Criar ISO bootável com GRUB
iso: kernel.elf
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp kernel.elf $(ISO_DIR)/boot/kernel.elf
	@echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "knl64 Kernel" {' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    multiboot2 /boot/kernel.elf' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    boot' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}' >> $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue -o knl64.iso $(ISO_DIR) 2>/dev/null || echo "Aviso: grub-mkrescue não encontrado"
	@echo "ISO criado: knl64.iso"

# Executar com QEMU
run: iso
	qemu-system-x86_64 -cdrom knl64.iso

# Limpar arquivos gerados
clean:
	@rm -f $(OBJECTS) kernel.elf knl64.iso
	@rm -rf $(ISO_DIR)
	@echo "Arquivos limpos"