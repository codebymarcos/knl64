/**
 * Módulo de boot do kernel knl64.
 * Contém funções para inicialização básica e saída de console VGA.
 */

#include "boot.h"

// Ponteiro para a memória VGA text mode
static volatile unsigned short *vga_buffer = (unsigned short *)0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static const unsigned char VGA_COLOR = 0x07; // Cinza claro no preto

/**
 * Inicializa o console para saída básica.
 * Limpa a tela VGA.
 */
void init_console(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = ((unsigned short)VGA_COLOR << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

/**
 * Imprime um caractere no console.
 * @param c Caractere a ser impresso.
 */
static void putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        const int index = cursor_y * VGA_WIDTH + cursor_x;
        vga_buffer[index] = ((unsigned short)VGA_COLOR << 8) | c;
        cursor_x++;
        
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    
    // Scroll se necessário
    if (cursor_y >= VGA_HEIGHT) {
        for (int y = 1; y < VGA_HEIGHT; y++) {
            for (int x = 0; x < VGA_WIDTH; x++) {
                vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
            }
        }
        
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = ((unsigned short)VGA_COLOR << 8) | ' ';
        }
        cursor_y = VGA_HEIGHT - 1;
    }
}

/**
 * Imprime uma string no console.
 * @param str String a ser impressa.
 */
void print(const char *str) {
    while (*str) {
        putchar(*str);
        str++;
    }
}