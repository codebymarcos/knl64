/**
 * Implementação do gerenciador de memória física do kernel knl64.
 * Usa um bitmap para rastrear páginas livres e ocupadas.
 */

#include "memory.h"

// Bitmap para rastrear páginas (1 bit por página)
static uint32_t *page_bitmap = NULL;
static size_t total_pages = 0;
static size_t free_pages = 0;
static uintptr_t memory_start = 0;

// Funções auxiliares para manipular bits
static inline void set_bit(uint32_t *bitmap, size_t bit) {
    bitmap[bit / 32] |= (1 << (bit % 32));
}

static inline void clear_bit(uint32_t *bitmap, size_t bit) {
    bitmap[bit / 32] &= ~(1 << (bit % 32));
}

static inline int test_bit(uint32_t *bitmap, size_t bit) {
    return (bitmap[bit / 32] & (1 << (bit % 32))) != 0;
}

/**
 * Inicializa o gerenciador de memória física.
 * @param mem_lower Limite inferior da memória em KB (não usado nesta implementação).
 * @param mem_upper Limite superior da memória em KB.
 */
void init_memory_manager(uint32_t mem_lower, uint32_t mem_upper) {
    (void)mem_lower; // Evitar warning de variável não usada
    
    // Calcular tamanho total da memória em bytes
    size_t total_memory = (size_t)mem_upper * 1024;
    
    // Calcular número total de páginas
    total_pages = total_memory / PAGE_SIZE;
    
    // Tamanho do bitmap em uint32_t (cada uint32_t tem 32 bits)
    size_t bitmap_size = (total_pages + 31) / 32;
    
    // Colocar bitmap após o kernel (assumindo que kernel termina em 2MB)
    memory_start = 0x200000; // 2MB
    page_bitmap = (uint32_t *)memory_start;
    
    // Zerar bitmap (todas as páginas livres inicialmente)
    for (size_t i = 0; i < bitmap_size; i++) {
        page_bitmap[i] = 0;
    }
    
    // Marcar páginas do bitmap e do kernel como ocupadas
    size_t bitmap_pages = (bitmap_size * sizeof(uint32_t) + PAGE_SIZE - 1) / PAGE_SIZE;
    size_t kernel_pages = (memory_start / PAGE_SIZE) + bitmap_pages;
    
    for (size_t i = 0; i < kernel_pages; i++) {
        set_bit(page_bitmap, i);
    }
    
    free_pages = total_pages - kernel_pages;
}

/**
 * Aloca uma página física.
 * @return Ponteiro para a página alocada, ou NULL se não houver páginas disponíveis.
 */
void *alloc_page(void) {
    if (free_pages == 0) {
        return NULL; // Sem páginas disponíveis
    }
    
    // Procurar primeira página livre
    for (size_t i = 0; i < total_pages; i++) {
        if (!test_bit(page_bitmap, i)) {
            set_bit(page_bitmap, i);
            free_pages--;
            return (void *)(i * PAGE_SIZE);
        }
    }
    
    return NULL; // Não deveria chegar aqui
}

/**
 * Libera uma página física.
 * @param page Ponteiro para a página a ser liberada.
 */
void free_page(void *page) {
    if (page == NULL) {
        return;
    }
    
    uintptr_t addr = (uintptr_t)page;
    size_t page_index = addr / PAGE_SIZE;
    
    if (page_index >= total_pages) {
        return; // Endereço inválido
    }
    
    if (!test_bit(page_bitmap, page_index)) {
        return; // Página já está livre
    }
    
    clear_bit(page_bitmap, page_index);
    free_pages++;
}

/**
 * Obtém o número total de páginas gerenciadas.
 * @return Número total de páginas.
 */
size_t get_total_pages(void) {
    return total_pages;
}

/**
 * Obtém o número de páginas livres.
 * @return Número de páginas livres.
 */
size_t get_free_pages(void) {
    return free_pages;
}