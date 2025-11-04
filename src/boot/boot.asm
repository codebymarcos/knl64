; Arquivo de boot do kernel knl64
; Configurado para carregar com GRUB2 usando Multiboot2

section .multiboot
align 8
multiboot_header_start:
    dd 0xE85250D6                ; magic number (multiboot2)
    dd 0                         ; architecture 0 (protected mode i386)
    dd multiboot_header_end - multiboot_header_start
    dd 0x100000000 - (0xE85250D6 + 0 + (multiboot_header_end - multiboot_header_start))
    
    ; end tag
    dw 0
    dw 0
    dd 8
multiboot_header_end:

[bits 32]
section .text
global _start

_start:
    ; Desabilitar interrupções
    cli
    
    ; Configurar stack
    mov esp, stack_top
    
    ; Verificar suporte a modo longo (CPUID)
    call check_long_mode
    
    ; Configurar paging para modo longo
    call setup_page_tables
    call enable_paging
    
    ; Carregar GDT de 64 bits
    lgdt [gdt64.pointer]
    
    ; Entrar em modo longo
    jmp gdt64.code:long_mode_start

check_long_mode:
    ; Verificar se CPUID é suportado
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_long_mode
    
    ; Verificar modo longo disponível
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode
    
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret
    
.no_long_mode:
    hlt

setup_page_tables:
    ; Mapear primeira entrada P4 para P3
    mov eax, p3_table
    or eax, 0b11  ; present + writable
    mov [p4_table], eax
    
    ; Mapear primeira entrada P3 para P2
    mov eax, p2_table
    or eax, 0b11
    mov [p3_table], eax
    
    ; Mapear cada entrada P2 (512 entradas de 2MB cada)
    mov ecx, 0
.map_p2_table:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011  ; present + writable + huge
    mov [p2_table + ecx * 8], eax
    inc ecx
    cmp ecx, 512
    jne .map_p2_table
    ret

enable_paging:
    ; Carregar P4 no CR3
    mov eax, p4_table
    mov cr3, eax
    
    ; Habilitar PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    
    ; Habilitar modo longo
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    
    ; Habilitar paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    ret

[bits 64]
long_mode_start:
    ; Zerar registradores de segmento
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Configurar stack
    mov rsp, stack_top
    
    ; Chamar função principal do kernel
    extern kmain
    call kmain
    
    ; Loop infinito se kmain retornar
.loop:
    hlt
    jmp .loop

section .rodata
gdt64:
    dq 0
.code: equ $ - gdt64
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53)  ; code segment
.data: equ $ - gdt64
    dq (1<<44) | (1<<47)  ; data segment
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .bss
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096
stack_bottom:
    resb 16384  ; 16KB stack
stack_top: