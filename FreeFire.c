#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
} CriterioOrdenacao;

void adicionarComponente(Item mochila[], int* numItens, bool* ordenadaPorNome);
void listarComponentes(const Item mochila[], int numItens);
void descartarComponente(Item mochila[], int* numItens);
void organizarMochila(Item mochila[], int numItens, bool* ordenadaPorNome, int* comparacoes);
void buscaBinariaPorNome(const Item mochila[], int numItens, bool ordenadaPorNome);

#define MAX_ITENS 10

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
int main() {
    // Vetor mochila:
    // Armazena até 10 itens coletados.
    // Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int comparacoes = 0;
    bool ordenadaPorNome = false;

    int opcao;

    do {
        printf("\n===================================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("===================================================\n");
        printf("Itens na mochila: %d/10\n", numItens);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadaPorNome ? "ORDENADA" : "NAO ORDENADA");

        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarComponente(mochila, &numItens, &ordenadaPorNome);
                listarComponentes(mochila, numItens);
                break;
            case 2:
                descartarComponente(mochila, &numItens);
                listarComponentes(mochila, numItens);
                break;
            case 3:
                listarComponentes(mochila, numItens);
                break;
            case 4:
                organizarMochila(mochila, numItens, &ordenadaPorNome, &comparacoes);
                listarComponentes(mochila, numItens);
                break;
            case 5:
                buscaBinariaPorNome(mochila, numItens, ordenadaPorNome);
                break;
            case 0:
                printf("Saindo do sistema. Até a próxima partida!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void adicionarComponente(Item mochila[], int *numItens, bool* ordenadaPorNome) {
    printf("\n--- Coletando Novo Componente ---\n");

    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais componentes.\n");
        return;
    }

    Item novoItem;
    printf("Nome: ");
    scanf("%s", novoItem.nome);
    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf("%s", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &novoItem.prioridade);

    if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
        printf("Prioridade invalida! Deve ser entre 1 e 5.\n");
        return;
    }

    mochila[*numItens] = novoItem;
    (*numItens)++;
    *ordenadaPorNome = false;

    printf("Componente '%s' adicionado!\n\n", novoItem.nome);
}

void listarComponentes(const Item mochila[], int numItens) {
    printf("\n--- INVENTARIO ATUAL (%d/10) ---\n", numItens);

    if (numItens == 0) {
        printf("A mochila esta vazia.\n\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s | %-15s | %-10d | %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("---------------------------------------------------------------\n\n");

    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer
    getchar(); // Espera o Enter
}

void descartarComponente(Item mochila[], int *numItens) {
    printf("\n--- Descartar Componente ---\n");

    if (*numItens == 0) {
        printf("Mochila vazia! Nao ha componentes para descartar.\n");
        return;
    }

    char nomeDescartar[30];
    printf("Digite o nome do componente a ser descartado: ");
    scanf("%s", nomeDescartar);

    bool encontrado = false;

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeDescartar) == 0) {
            encontrado = true;
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("Componente '%s' descartado com sucesso!\n\n", nomeDescartar);
            break;
        }
    }

    if (!encontrado) {
        printf("Componente '%s' nao encontrado na mochila.\n\n", nomeDescartar);
    }
}

void organizarMochila(Item mochila[], int numItens, bool* ordenadaPorNome, int* comparacoes) {
    if (numItens == 0) {
        printf("\nMochila vazia! Nao ha componentes para organizar.\n");
        return;
    }

    CriterioOrdenacao criterio;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &criterio);

    *comparacoes = 0;

    switch (criterio) {
        case POR_NOME:
            for (int i = 1; i < numItens; i++) {
                Item chave = mochila[i];
                int j = i - 1;
                
                // Move elementos maiores que a chave para frente
                while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {
                    (*comparacoes)++;
                    mochila[j + 1] = mochila[j];
                    j--;
                }

                // Conta a última comparação que fez
                if (j >= 0) (*comparacoes)++;
                
                mochila[j + 1] = chave;
            }

            *ordenadaPorNome = true;

            printf("\n\nMochila organizada por NOME.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n\n", *comparacoes);
            break;
        case POR_TIPO:
            for (int i = 1; i < numItens; i++) {
                Item chave = mochila[i];
                int j = i - 1;
                
                while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
                    (*comparacoes)++;
                    mochila[j + 1] = mochila[j];
                    j--;
                }
                
                if (j >= 0) (*comparacoes)++;
                
                mochila[j + 1] = chave;
            }

            *ordenadaPorNome = false;

            printf("\n\nMochila organizada por TIPO.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n\n", *comparacoes);
            break;
        case POR_PRIORIDADE:
            for (int i = 1; i < numItens; i++) {
                Item chave = mochila[i];
                int j = i - 1;
                
                while (j >= 0 && mochila[j].prioridade > chave.prioridade) {
                    (*comparacoes)++;
                    mochila[j + 1] = mochila[j];
                    j--;
                }
                
                if (j >= 0) (*comparacoes)++;
                
                mochila[j + 1] = chave;
            }

            *ordenadaPorNome = false;

            printf("\n\nMochila organizada por PRIORIDADE.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n\n", *comparacoes);
            break;
        case 0:
            break;
    }
}

void buscaBinariaPorNome(const Item mochila[], int numItens, bool ordenadaPorNome) {
    if (!ordenadaPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a opcao 4 para organizar a mochila primeiro.\n\n");

        printf("Pressione Enter para continuar...");
        while (getchar() != '\n'); // Limpa o buffer
        getchar(); // Espera o Enter
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a buscar: ");
    scanf("%s", nomeBusca);

    int esquerda = 0;
    int direita = numItens - 1;
    int meio;

    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;

        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("\n--- Componente-Chave Encontrado! ---\n");
            printf("Nome: %s, Tipo: %s, Qtd: %d, Prio: %d\n\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            
            printf("Pressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar(); // Espera o Enter
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    printf("\nResultado: Componente-Chave '%s' NAO foi encontrado na mochila.\n\n", nomeBusca);
}