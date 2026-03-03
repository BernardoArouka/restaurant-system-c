#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_VENDAS "vendas.bin"
#define PRECO_POR_KG 20.00
#define CUSTO_EMBALAGEM 0.50

// Enum para tipos de bebida
typedef enum {
    BEBIDA_NENHUMA = 0,
    BEBIDA_REFRIGERANTE = 1,
    BEBIDA_SUCO = 2,
    BEBIDA_AGUA = 3
} TipoBebida;

// Estrutura que representa uma venda
typedef struct {
    char data[11]; // Formato dd/mm/yyyy
    float peso_refeicao;
    int tem_bebida;
    TipoBebida tipo_bebida;
    int quantidade_bebida;
    float valor_total;
} Venda;

// Declaracao das funcoes principais
void registrarVenda();
void relatorioDiario();
void relatorioMensal();
void ordenarPorValor();
void limparHistorico();

// Declaracao de funcoes auxiliares
float obterPrecoBebida(TipoBebida tipo);
const char* obterNomeBebida(TipoBebida tipo);
void exibirVenda(const Venda *v);
int validarData(const char* data);

int main() {
    int opcao;

    do {
        // Menu principal do sistema
        printf("\n===== MENU RESTAURANTE A QUILO (COM DATA) =====\n");
        printf("1 - Registrar nova venda\n");
        printf("2 - Mostrar relatorio de um dia especifico\n");
        printf("3 - Mostrar relatorio de um mes especifico\n");
        printf("4 - Mostrar vendas ordenadas por valor total\n");
        printf("5 - Limpar historico de vendas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n deixado pelo scanf

        switch (opcao) {
            case 1:
                registrarVenda();
                break;
            case 2:
                relatorioDiario();
                break;
            case 3:
                relatorioMensal();
                break;
            case 4:
                ordenarPorValor();
                break;
            case 5:
                limparHistorico();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Nova função para limpar o histórico de vendas
void limparHistorico() {
    FILE *fp = fopen(ARQUIVO_VENDAS, "wb"); // Abre em modo escrita binária (zera o arquivo)
    if (fp == NULL) {
        printf("Erro ao tentar limpar o historico de vendas.\n");
        return;
    }
    fclose(fp);
    printf("Historico de vendas apagado com sucesso.\n");
}

// Função para registrar uma nova venda
void registrarVenda() {
    Venda nova = {0};

    // Solicita a data e valida o formato (dd/mm/yyyy)
    printf("Digite a data da venda (formato dd/mm/yyyy): ");
    fgets(nova.data, sizeof(nova.data), stdin);
    nova.data[strcspn(nova.data, "\n")] = '\0';

    if (!validarData(nova.data)) {
        printf("Data invalida. Use o formato dd/mm/yyyy.\n");
        return;
    }

    // Solicita o peso da refeição
    printf("Peso da refeicao (kg): ");
    scanf("%f", &nova.peso_refeicao);

    // Calcula o valor total da refeição
    nova.valor_total = (PRECO_POR_KG * nova.peso_refeicao) + CUSTO_EMBALAGEM;

    // Pergunta se o cliente deseja bebida
    char resposta;
    printf("Deseja adicionar bebida? (s/n): ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        nova.tem_bebida = 1;
        int opcao;
        printf("Escolha a bebida:\n");
        printf("1 - Refrigerante (R$ 5.00)\n");
        printf("2 - Suco         (R$ 4.00)\n");
        printf("3 - Agua         (R$ 2.00)\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 3) {
            nova.tipo_bebida = (TipoBebida)opcao;
            printf("Quantidade: ");
            scanf("%d", &nova.quantidade_bebida);
            nova.valor_total += obterPrecoBebida(nova.tipo_bebida) * nova.quantidade_bebida;
        } else {
            printf("Bebida invalida. Nenhuma bebida adicionada.\n");
            nova.tem_bebida = 0;
        }
    }

    // Salva a venda no arquivo binário
    FILE *fp = fopen(ARQUIVO_VENDAS, "ab");
    if (!fp) {
        perror("Erro ao abrir arquivo para salvar venda");
        return;
    }

    fwrite(&nova, sizeof(Venda), 1, fp);
    fclose(fp);

    printf("Venda registrada com sucesso!\n");
}

// Relatório de vendas por data específica
void relatorioDiario() {
    char data_busca[11];
    printf("Digite a data do relatorio (formato dd/mm/yyyy): ");
    fgets(data_busca, sizeof(data_busca), stdin);
    data_busca[strcspn(data_busca, "\n")] = '\0';

    if (!validarData(data_busca)) {
        printf("Data invalida. Use o formato dd/mm/yyyy.\n");
        return;
    }

    FILE *fp = fopen(ARQUIVO_VENDAS, "rb");
    if (!fp) {
        printf("Nenhuma venda registrada ainda.\n");
        return;
    }

    printf("\n===== RELATORIO DO DIA %s =====\n", data_busca);
    Venda v;
    int encontrou = 0;
    while (fread(&v, sizeof(Venda), 1, fp) == 1) {
        if (strcmp(v.data, data_busca) == 0) {
            exibirVenda(&v);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma venda encontrada para esta data.\n");
    }

    fclose(fp);
}

// Relatório de vendas de um mês específico
void relatorioMensal() {
    char mes_ano[8]; // formato mm/yyyy
    printf("Digite o mes do relatorio (formato mm/yyyy): ");
    fgets(mes_ano, sizeof(mes_ano), stdin);
    mes_ano[strcspn(mes_ano, "\n")] = '\0';

    if (strlen(mes_ano) != 7 || mes_ano[2] != '/') {
        printf("Formato invalido. Use mm/yyyy.\n");
        return;
    }

    FILE *fp = fopen(ARQUIVO_VENDAS, "rb");
    if (!fp) {
        printf("Nenhuma venda registrada ainda.\n");
        return;
    }

    printf("\n===== RELATORIO MENSAL - %s =====\n", mes_ano);
    Venda v;
    int contador = 0;
    float total = 0.0;
    while (fread(&v, sizeof(Venda), 1, fp) == 1) {
        if (strncmp(v.data + 3, mes_ano, 7) == 0) {
            exibirVenda(&v);
            total += v.valor_total;
            contador++;
        }
    }

    if (contador == 0) {
        printf("Nenhuma venda encontrada para este mes.\n");
    } else {
        printf("\nTotal de vendas: %d\n", contador);
        printf("Total arrecadado: R$ %.2f\n", total);
    }

    fclose(fp);
}

// Ordena as vendas pelo valor total (decrescente)
void ordenarPorValor() {
    FILE *fp = fopen(ARQUIVO_VENDAS, "rb");
    if (!fp) {
        printf("Nenhuma venda registrada ainda.\n");
        return;
    }

    Venda vendas[500];
    int n = 0;
    while (fread(&vendas[n], sizeof(Venda), 1, fp) == 1) {
        n++;
    }
    fclose(fp);

    // Ordenacao simples por valor (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vendas[i].valor_total < vendas[j].valor_total) {
                Venda temp = vendas[i];
                vendas[i] = vendas[j];
                vendas[j] = temp;
            }
        }
    }

    printf("\n===== VENDAS ORDENADAS POR VALOR TOTAL =====\n");
    for (int i = 0; i < n; i++) {
        exibirVenda(&vendas[i]);
    }
}

// Retorna o preco da bebida
float obterPrecoBebida(TipoBebida tipo) {
    switch (tipo) {
        case BEBIDA_REFRIGERANTE: return 5.00;
        case BEBIDA_SUCO: return 4.00;
        case BEBIDA_AGUA: return 2.00;
        default: return 0.0;
    }
}

// Retorna o nome da bebida como string
const char* obterNomeBebida(TipoBebida tipo) {
    switch (tipo) {
        case BEBIDA_REFRIGERANTE: return "Refrigerante";
        case BEBIDA_SUCO: return "Suco";
        case BEBIDA_AGUA: return "Agua";
        default: return "Nenhuma";
    }
}

// Exibe os dados formatados de uma venda
void exibirVenda(const Venda *v) {
    printf("Data: %s\n", v->data);
    float valor_refeicao = (PRECO_POR_KG * v->peso_refeicao) + CUSTO_EMBALAGEM;
    printf("  Refeicao | Peso: %.2f kg | Total: R$ %.2f\n", v->peso_refeicao, valor_refeicao);

    if (v->tem_bebida) {
        float preco = obterPrecoBebida(v->tipo_bebida);
        float total = preco * v->quantidade_bebida;
        printf("  Bebida   | Tipo: %s | Qtde: %d | Unit: R$ %.2f | Total: R$ %.2f\n",
               obterNomeBebida(v->tipo_bebida), v->quantidade_bebida, preco, total);
    }

    printf("  TOTAL DA VENDA: R$ %.2f\n\n", v->valor_total);
}

// Valida o formato da data dd/mm/yyyy
int validarData(const char* data) {
    if (strlen(data) != 10) return 0;
    return data[2] == '/' && data[5] == '/';
}
