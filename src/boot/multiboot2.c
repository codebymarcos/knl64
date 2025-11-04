/**
 * Implementação do parser de informações Multiboot2.
 * Extrai dados de memória passados pelo GRUB.
 */

#include <stddef.h>
#include "multiboot2.h"

/**
 * Processa informações do Multiboot2.
 * @param mbi Ponteiro para a estrutura de informações do Multiboot2.
 * @param mem_lower Ponteiro para armazenar memória inferior (KB).
 * @param mem_upper Ponteiro para armazenar memória superior (KB).
 */
void parse_multiboot2_info(struct multiboot2_info *mbi, uint32_t *mem_lower, uint32_t *mem_upper) {
    if (mbi == NULL || mem_lower == NULL || mem_upper == NULL) {
        return;
    }
    
    // Valores padrão caso não encontre tags
    *mem_lower = 0;
    *mem_upper = 128 * 1024; // 128MB padrão
    
    // Iterar sobre as tags
    struct multiboot2_tag *tag;
    for (tag = (struct multiboot2_tag *)((uint8_t *)mbi + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot2_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7))) {
        
        if (tag->type == MULTIBOOT_TAG_TYPE_BASIC_MEMINFO) {
            struct multiboot2_tag_basic_meminfo *meminfo = 
                (struct multiboot2_tag_basic_meminfo *)tag;
            *mem_lower = meminfo->mem_lower;
            *mem_upper = meminfo->mem_upper;
            return; // Encontrou, pode retornar
        }
    }
}