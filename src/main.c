/**
 * Arquivo principal do kernel knl64.
 * Este arquivo contém o ponto de entrada do kernel após a inicialização do boot.
 */

#include "boot/boot.h"
#include "boot/multiboot2.h"
#include "memory/memory.h"

/**
 * Converte um número para string hexadecimal.
 * @param num Número a ser convertido.
 * @param str Buffer para armazenar a string (mínimo 19 bytes).
 */
static void uint_to_hex_str(size_t num, char *str) {
    const char hex_chars[] = "0123456789ABCDEF";
    int i = 0;
    
    str[i++] = '0';
    str[i++] = 'x';
    
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    char temp[17];
    int j = 0;
    
    while (num > 0) {
        temp[j++] = hex_chars[num % 16];
        num /= 16;
    }
    
    while (j > 0) {
        str[i++] = temp[--j];
    }
    
    str[i] = '\0';
}

/**
 * Função principal do kernel.
 * Inicializa os subsistemas básicos e entra no loop principal.
 * @param multiboot2_info Ponteiro para estrutura de informações do Multiboot2.
 */
void kmain(struct multiboot2_info *multiboot2_info) {
    char buffer[32];
    uint32_t mem_lower = 0;
    uint32_t mem_upper = 0;
    
    // Inicializar console
    init_console();
    print("Kernel knl64 iniciado com sucesso!\n\n");

    // Parsear informações do Multiboot2
    print("Detectando memoria via Multiboot2...\n");
    parse_multiboot2_info(multiboot2_info, &mem_lower, &mem_upper);
    
    print("Memoria inferior: ");
    uint_to_hex_str(mem_lower, buffer);
    print(buffer);
    print(" KB\n");
    
    print("Memoria superior: ");
    uint_to_hex_str(mem_upper, buffer);
    print(buffer);
    print(" KB\n\n");

    // Inicializar gerenciador de memória com valores detectados
    print("Inicializando gerenciador de memoria...\n");
    init_memory_manager(mem_lower, mem_upper);
    
    print("Total de paginas: ");
    uint_to_hex_str(get_total_pages(), buffer);
    print(buffer);
    print("\n");
    
    print("Paginas livres: ");
    uint_to_hex_str(get_free_pages(), buffer);
    print(buffer);
    print("\n\n");

    // Testar alocação de páginas
    print("Testando alocacao de paginas...\n");
    void *page1 = alloc_page();
    void *page2 = alloc_page();
    void *page3 = alloc_page();
    
    print("Pagina 1 alocada em: ");
    uint_to_hex_str((size_t)page1, buffer);
    print(buffer);
    print("\n");
    
    print("Pagina 2 alocada em: ");
    uint_to_hex_str((size_t)page2, buffer);
    print(buffer);
    print("\n");
    
    print("Pagina 3 alocada em: ");
    uint_to_hex_str((size_t)page3, buffer);
    print(buffer);
    print("\n\n");
    
    print("Paginas livres apos alocacao: ");
    uint_to_hex_str(get_free_pages(), buffer);
    print(buffer);
    print("\n\n");

    // Testar liberação de páginas
    print("Liberando pagina 2...\n");
    free_page(page2);
    
    print("Paginas livres apos liberacao: ");
    uint_to_hex_str(get_free_pages(), buffer);
    print(buffer);
    print("\n\n");
    
    print("Gerenciador de memoria testado com sucesso!\n");

    // Loop infinito para manter o kernel rodando
    while (1) {
        // TODO: Implementar scheduler ou idle loop
    }
}