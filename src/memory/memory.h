/**
 * Header para gerenciamento de memória física do kernel knl64.
 * Implementa alocação e liberação de páginas usando bitmap.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

// Tamanho de uma página (4KB)
#define PAGE_SIZE 4096

/**
 * Inicializa o gerenciador de memória física.
 * @param mem_lower Limite inferior da memória em KB.
 * @param mem_upper Limite superior da memória em KB.
 */
void init_memory_manager(uint32_t mem_lower, uint32_t mem_upper);

/**
 * Aloca uma página física.
 * @return Ponteiro para a página alocada, ou NULL se não houver páginas disponíveis.
 */
void *alloc_page(void);

/**
 * Libera uma página física.
 * @param page Ponteiro para a página a ser liberada.
 */
void free_page(void *page);

/**
 * Obtém o número total de páginas gerenciadas.
 * @return Número total de páginas.
 */
size_t get_total_pages(void);

/**
 * Obtém o número de páginas livres.
 * @return Número de páginas livres.
 */
size_t get_free_pages(void);

#endif // MEMORY_H