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
} Item;

void inserirItem(Item mochila[], int* numItens);
void removerItem(Item mochila[], int* numItens);
void listarItens(const Item mochila[], int numItens);
void buscarItemPorNome(const Item mochila[], int numItens);


#define MAX_ITENS 10

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int comparacoes = 0;
    bool ordenadaPorNome = false;

    int opcao;

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    do {
        printf("\n======================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("======================================\n");
        printf("Itens na mochila: %d/10\n\n", numItens);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("--------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItemPorNome(mochila, numItens);
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

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(Item mochila[], int *numItens) {
    printf("\n--- Adicionar Novo Item ---\n");

    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Nome do item: ");
    scanf("%s", novoItem.nome);
    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[*numItens] = novoItem;
    (*numItens)++;

    printf("Item '%s' adicionado com sucesso!\n\n", novoItem.nome);
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem(Item mochila[], int *numItens) {
    printf("\n--- Remover Item ---\n");

    if (*numItens == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("Item '%s' removido com sucesso!\n\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n\n", nomeRemover);
    }
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(const Item mochila[], int numItens) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", numItens);

    if (numItens == 0) {
        printf("A mochila esta vazia.\n\n");
        return;
    }

    printf("\n-----------------------------------------------------\n");
    printf("%-20s | %-20s | %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s | %-20s | %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("-----------------------------------------------------\n\n");

    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer
    getchar(); // Espera o Enter
}


void buscarItemPorNome(const Item mochila[], int numItens) {
    printf("\n--- Buscar Item na Mochila ---\n");

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    bool encontrado = false;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = true;
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("-------------------------\n\n");
            break;
        }
    }

    if (!encontrado) printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n\n", nomeBusca);

    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer
    getchar(); // Espera o Enter
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
