/**
 * Header para o módulo de boot.
 * Declara funções de inicialização e saída.
 * Nota: Este boot assume que um bootloader externo (ex.: GRUB) já configurou o modo longo.
 */

#ifndef BOOT_H
#define BOOT_H

/**
 * Inicializa o console.
 */
void init_console(void);

/**
 * Imprime uma string no console.
 * @param str Ponteiro para a string null-terminated.
 */
void print(const char *str);

#endif // BOOT_H