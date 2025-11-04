# Diretrizes de Programação em C e Assembly para Desenvolvimento do Kernel knl64

## Visão Geral
Este projeto desenvolve um kernel de 64 bits (knl64) seguindo um roadmap em fases no arquivo `.md`. O código deve ser escrito em C para a lógica principal e assembly para partes de baixo nível, visando segurança e performance. Siga estas regras para código limpo, compacto e documentado, com funções e arquivos independentes.

## Estilo e Estrutura do Código
- **Compacto e Limpo**: Use expressões concisas. Evite código desnecessário. Prefira estilo procedural claro.
- **Funções Independentes**: Cada função deve ter uma única responsabilidade. Mantenha funções pequenas (<50 linhas). Use nomes claros e descritivos.
- **Arquivos Independentes**: Organize o código em módulos. Um conceito principal por arquivo. Use includes para headers.
- **Convenções de Nomenclatura**: Use snake_case para funções/variáveis, PascalCase para tipos/structs. Prefixe funções inseguras ou críticas com comentários.
- **Tratamento de Erros**: Use códigos de retorno ou errno para erros. Evite asserts em produção; use logs para debug.

## Documentação
- **Comentários em PT-BR**: Todos os comentários e docs em português brasileiro.
- **Comentários de Doc**: Use `/** */` para APIs públicas. Inclua exemplos quando útil.
- **Comentários Inline**: Explique lógica complexa brevemente. Evite comentários óbvios.
- **READMEs**: Cada arquivo de módulo deve ter um comentário de cabeçalho descrevendo seu propósito.

## Boas Práticas
- **Segurança Primeiro**: Minimize código inseguro. Justifique acessos diretos à memória com comentários.
- **Performance**: Use estruturas de dados eficientes. Perfile gargalos.
- **Testes**: Escreva testes unitários para cada função. Testes de integração para módulos (usando frameworks como CUnit).
- **Dependências**: Minimize bibliotecas externas. Prefira stdlib ou libs pequenas e confiáveis.
- **Controle de Versão**: Faça commits frequentes. Use mensagens descritivas.

## Modularidade para Ajustes
- **Separe Preocupações**: Isole boot, memória, processos, etc., em módulos distintos (ex.: `boot.c`, `memory.c`).
- **Interfaces**: Defina headers (.h) para abstrações. Implemente em arquivos .c separados.
- **Configuração**: Use defines ou arquivos de config para parâmetros ajustáveis.

## Estrutura de Diretórios e Arquivos
Para manter um código limpo e um projeto profissional, organize os arquivos em pastas lógicas baseadas nas prioridades do roadmap em `.md`. Cada pasta deve conter apenas arquivos relacionados a um conceito específico, facilitando ajustes e melhorias.

- **src/**: Código fonte principal.
  - **boot/**: Inicialização e integração com bootloader (BIOS/UEFI).
  - **memory/**: Gerenciamento de memória física (RAM) e virtual (MMU).
  - **process/**: Scheduler e gerenciamento de processos.
  - **syscall/**: Interface usuário-kernel e syscalls.
  - **interrupt/**: Tratamento de interrupções (IDT/ISRs) e timers.
  - **drivers/**: Drivers básicos (console, bloco, dispositivos).
  - **fs/**: Sistema de arquivos simples e VFS.
  - **main.c**: Ponto de entrada principal.
- **tests/**: Testes unitários e de integração.
- **docs/**: Documentação adicional, como READMEs por módulo.
- **build/**: Scripts de build, toolchain e configurações (ex.: Makefile, linker scripts).
- **.github/**: Workflows de CI/CD, issues templates e este arquivo de instruções.

Mantenha arquivos pequenos e focados. Use includes em headers para declarar módulos. Evite misturar responsabilidades entre pastas.

## Exemplos
- Função: `int allocate_page(page_t *page)` - Propósito único, documentada.
- Arquivo: `memory.c` - Apenas funções de gerenciamento de memória, sem I/O.

Siga o roadmap no `.md` para prioridades de recursos. Comece com os essenciais da Prioridade A.
