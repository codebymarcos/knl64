/**
 * Arquivo principal do kernel knl64.
 * Este arquivo contém o ponto de entrada do kernel após a inicialização do boot.
 */

#include "boot/boot.h"  // Incluir header do boot se necessário

/**
 * Função principal do kernel.
 * Inicializa os subsistemas básicos e entra no loop principal.
 */
void kmain(void) {
    // Inicializar console ou saída básica
    init_console();

    // Imprimir mensagem de inicialização
    print("Kernel knl64 iniciado com sucesso!\n");

    // TODO: Inicializar memória, interrupções, processos, etc.

    // Loop infinito para manter o kernel rodando
    while (1) {
        // TODO: Implementar scheduler ou idle loop
    }
}