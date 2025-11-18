#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 100

typedef struct NoTarefa {
    int id;
    char descricao[MAX_DESCRICAO];
    struct NoTarefa *proximo;
} NoTarefa;

NoTarefa *cabeca = NULL;
int proximo_id = 1;

void adicionarTarefa(const char *descricao) {
    NoTarefa *novoNo = (NoTarefa *)malloc(sizeof(NoTarefa));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return;
    }

    novoNo->id = proximo_id++;
    strncpy(novoNo->descricao, descricao, MAX_DESCRICAO - 1);
    novoNo->descricao[MAX_DESCRICAO - 1] = '\0';
    novoNo->proximo = NULL;

    if (cabeca == NULL) {
        cabeca = novoNo;
    } else {
        NoTarefa *atual = cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    printf("Tarefa #%d adicionada: %s\n", novoNo->id, novoNo->descricao);
}

void listarTarefas() {
    if (cabeca == NULL) {
        printf("A lista de tarefas esta vazia!\n");
        return;
    }

    printf("\n--- Lista de Tarefas Pendentes ---\n");
    NoTarefa *atual = cabeca;
    while (atual != NULL) {
        printf("[#%d] %s\n", atual->id, atual->descricao);
        atual = atual->proximo;
    }
    printf("----------------------------------\n");
}

void removerTarefa(int id) {
    NoTarefa *atual = cabeca;
    NoTarefa *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Tarefa com ID #%d nao encontrada.\n", id);
        return;
    }

    if (anterior == NULL) {
        cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    printf("Tarefa #%d removida: %s\n", atual->id, atual->descricao);
    free(atual);
}

void liberarMemoria() {
    NoTarefa *atual = cabeca;
    NoTarefa *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    cabeca = NULL;
}

void exibirMenu() {
    printf("\n--- Gerenciador de Tarefas ---\n");
    printf("1. Adicionar Nova Tarefa\n");
    printf("2. Listar Todas as Tarefas\n");
    printf("3. Remover Tarefa por ID\n");
    printf("4. Sair e Limpar Memoria\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao, id_remover;
    char descricao[MAX_DESCRICAO];

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = 0;
            printf("Opcao invalida. Por favor, digite um numero.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite a descricao da nova tarefa: ");
                while (getchar() != '\n'); 
                
                if (fgets(descricao, MAX_DESCRICAO, stdin) != NULL) {
                    descricao[strcspn(descricao, "\n")] = '\0'; 
                    adicionarTarefa(descricao);
                } else {
                    printf("Erro ao ler a descricao.\n");
                }
                break;
            case 2:
                listarTarefas();
                break;
            case 3:
                printf("Digite o ID da tarefa a remover: ");
                if (scanf("%d", &id_remover) == 1) {
                    removerTarefa(id_remover);
                } else {
                    printf("ID invalido.\n");
                    while (getchar() != '\n');
                }
                break;
            case 4:
                liberarMemoria();
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opcao desconhecida. Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}