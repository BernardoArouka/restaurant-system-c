# restaurant-system-c
Sistema de gerenciamento de restaurante a quilo em C | Sales management system for self-service restaurants
---
Projeto acadêmico - Engenharia de Computação (UVA)

Sobre:
Sistema desenvolvido em linguagem C para gestão de vendas em restaurantes self-service, realizando o cálculo automático de refeições por peso, soma de bebidas e persistência de dados em arquivos binários para controle de faturamento.

Funcionalidades
Cálculo de Consumo: Processamento do valor total baseado no peso da refeição (kg), preço por quilo e custo fixo de embalagem.

Gestão de Bebidas: Menu seletivo com diferentes categorias (Refrigerante, Suco, Água) e adição dinâmica ao valor final da venda.

Persistência de Dados: Armazenamento de registros em arquivo binário (vendas.bin), permitindo o fechamento e reabertura do sistema sem perda de informações.

Especificações Técnicas
Linguagem: C

Bibliotecas Utilizadas:

stdio.h: Operações de entrada e saída.
stdlib.h: Alocação e controle do sistema.
string.h: Manipulação de strings e validação de datas.

Compatibilidade: Desenvolvido para execução em terminal. O sistema utiliza manipulação de arquivos binários nativa da linguagem C.

Como Executar
Certifique-se de ter um compilador C instalado (GCC, Clang ou MinGW).

Abra o terminal e compile o arquivo:

Bash
gcc main.c -o restaurant_system
Execute o programa:

Bash
./restaurant_system
Fluxograma do Sistema
O fluxo lógico compreende o registro de venda (entrada de data e peso), seleção opcional de bebidas, cálculo do montante final, gravação em disco e módulos de consulta/ordenação para análise de dados.

---
Restaurant System in C
---
Academic Project - Computer Engineering (UVA)

About:
System developed in C for sales management in self-service restaurants, featuring automatic weight-based meal calculation, beverage integration, and binary file persistence for revenue control.

Features
Consumption Calculation: Automatic total value processing based on meal weight (kg), price per kilo, and fixed packaging costs.

Beverage Management: Selective menu with multiple categories (Soda, Juice, Water) and dynamic addition to the final bill.

Data Persistence: Records stored in a binary file (vendas.bin), allowing system restarts without data loss.

Technical Specifications
Language: C

Libraries:

stdio.h: I/O operations.

stdlib.h: System control.

string.h: String manipulation and data validation.

How to Run
Compilation:

Bash
gcc main.c -o restaurant_system
Execution:

Bash
./restaurant_system

System Flowchart
The program's logical flow follows sale registration (date and weight entry), optional beverage selection, total amount processing, disk storage, and query/sorting modules for data analysis.
