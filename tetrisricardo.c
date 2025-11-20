#include <stdio.h>


// definição das struct

typedef struct {
    char tipo;
    int id;
} Peca;

#define MAX_PECA 5

typedef struct {
    Peca itens[MAX_PECA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

// variáveis globais
int proximo_id_global = 0;

// criacao dos tipos de peças
char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
int indice_tipo_atual = 0;
int total_tipos = 7; // Quantidade de tipos determinada

// funções da Fila

void inicializarFila(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(FilaPecas *f) {
    return f->total == MAX_PECA;
}

int filaVazia(FilaPecas *f) {
    return f->total == 0;
}

void enqueue(FilaPecas *f, Peca p) {
    if (filaCheia(f)) {
        printf("ERRO: Fila de pecas cheia.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_PECA;
    f->total++;
}

Peca dequeue(FilaPecas *f) {
    if (filaVazia(f)) {
        printf("ERRO: Fila de pecas vazia.\n");
        Peca erro = {'X', -1}; 
        return erro;
    }

    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECA;
    f->total--;

    return removida;
}

void mostrarFila(FilaPecas *f) {
    printf("\n--- Fila de Pecas ---\n");
    if (filaVazia(f)) {
        printf("[ Fila vazia ]\n");
        return;
    }

    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_PECA) {
        printf("[%c ID:%d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n-----------------------\n");
}

// criacao de uma função para gerar uma peça de forma sequencial (considerando que nao se trata de uma forma aleatória)
Peca gerarPeca() {
    Peca nova_peca;
    
    nova_peca.tipo = tipos[indice_tipo_atual];
    indice_tipo_atual = (indice_tipo_atual + 1) % total_tipos;
    
    // atribuica de uma ID unica e insercao de um contador global
    nova_peca.id = proximo_id_global++;
    
    return nova_peca;
}

// funcao Principal e um menu de Interação

int main() {
    FilaPecas filaDoJogo;
    inicializarFila(&filaDoJogo);
    
    // Inicializacao da fila de peças com 5 elementos iniciais
    for (int i = 0; i < MAX_PECA; i++) {
        Peca p = gerarPeca();
        enqueue(&filaDoJogo, p);
    }

    int opcao = -1;

    while (opcao != 0) {
        mostrarFila(&filaDoJogo);
        
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Por gentileza, digite somente os numeros 1 ou 0.\n");
            while (getchar() != '\n'); 
            continue; 
        }

        switch (opcao) {
            case 1: {
                if (!filaVazia(&filaDoJogo)) {
                    Peca peca_jogada = dequeue(&filaDoJogo);
                    printf("\n>>> Voce jogou a peca [%c ID:%d]. <<<\n", peca_jogada.tipo, peca_jogada.id);
                    
                    // Insercao de uma nova peca automaticamente para manter a fila cheia
                    Peca nova_peca = gerarPeca();
                    enqueue(&filaDoJogo, nova_peca);
                    printf(">>> Nova peca [%c ID:%d] adicionada automaticamente ao final da fila. <<<\n", nova_peca.tipo, nova_peca.id);

                } else {
                    printf("\n>>> A fila atual esta vazia! <<<\n");
                }
                break;
            }
            case 0: {
                printf("Saindo do simulador.\n");
                break;
            }
            default: {
                printf("Opcao invalida. Por favor, tente novamente.\n");
                break;
            }
        }
        
        if (opcao != 0) {
           printf("\nPressione Enter para continuar...");
           while (getchar() != '\n'); 
           getchar(); 
        }
    }

    return 0;
}