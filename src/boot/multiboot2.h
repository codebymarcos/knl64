/**
 * Header para informações do bootloader Multiboot2.
 * Define estruturas para parsear tags passadas pelo GRUB.
 */

#ifndef MULTIBOOT2_H
#define MULTIBOOT2_H

#include <stdint.h>

// Estrutura do header Multiboot2 passado pelo bootloader
struct multiboot2_info {
    uint32_t total_size;
    uint32_t reserved;
};

// Tipos de tags Multiboot2
#define MULTIBOOT_TAG_TYPE_END 0
#define MULTIBOOT_TAG_TYPE_CMDLINE 1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME 2
#define MULTIBOOT_TAG_TYPE_MODULE 3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO 4
#define MULTIBOOT_TAG_TYPE_BOOTDEV 5
#define MULTIBOOT_TAG_TYPE_MMAP 6
#define MULTIBOOT_TAG_TYPE_VBE 7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS 9
#define MULTIBOOT_TAG_TYPE_APM 10
#define MULTIBOOT_TAG_TYPE_EFI32 11
#define MULTIBOOT_TAG_TYPE_EFI64 12

// Estrutura base de tag
struct multiboot2_tag {
    uint32_t type;
    uint32_t size;
};

// Tag de informação básica de memória
struct multiboot2_tag_basic_meminfo {
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
};

// Entrada do mapa de memória
struct multiboot2_mmap_entry {
    uint64_t addr;
    uint64_t len;
    uint32_t type;
    uint32_t zero;
} __attribute__((packed));

// Tag do mapa de memória
struct multiboot2_tag_mmap {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    struct multiboot2_mmap_entry entries[0];
};

// Tipos de memória no mmap
#define MULTIBOOT_MEMORY_AVAILABLE 1
#define MULTIBOOT_MEMORY_RESERVED 2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS 4
#define MULTIBOOT_MEMORY_BADRAM 5

/**
 * Processa informações do Multiboot2.
 * @param mbi Ponteiro para a estrutura de informações do Multiboot2.
 * @param mem_lower Ponteiro para armazenar memória inferior (KB).
 * @param mem_upper Ponteiro para armazenar memória superior (KB).
 */
void parse_multiboot2_info(struct multiboot2_info *mbi, uint32_t *mem_lower, uint32_t *mem_upper);

#endif // MULTIBOOT2_H