/* Linker script para kernel knl64 */

ENTRY(_start)

SECTIONS {
    . = 0x100000;  /* Endereço de carregamento do kernel */

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    .rodata : {
        *(.rodata)
    }
}