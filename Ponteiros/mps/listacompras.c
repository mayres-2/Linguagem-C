
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char nome[50];
    float valor;
    int quantidade;
} Compra;

void inserirCompra(Compra **lista, int *tamanhoLista);

void removerCompra(Compra **lista, int *tamanhoLista);

void removerGrupoCompra(Compra **lista, int *tamanhoLista);

void consultarLista(Compra *lista, int tamanhoLista);

void procurarCompra(Compra *lista, int tamanhoLista);


int main () {
    Compra *lista =NULL;
    int tamanhoLista = 0;
    char funcao[20];

    while (scanf("%s", funcao) != EOF){

        if(strcmp(funcao, "INSERIR") == 0){
            inserirCompra(&lista, &tamanhoLista);
        }
        else if(strcmp(funcao, "REMOVER") == 0){
            removerCompra(&lista, &tamanhoLista);
        }
        else if(strcmp(funcao, "REMOVERGRUPO") == 0){
            removerGrupoCompra(&lista, &tamanhoLista);
        }
        else if(strcmp(funcao, "CONSULTAR") == 0){
            consultarLista(lista, tamanhoLista);
        }
        else if(strcmp(funcao, "PROCURAR") == 0){
            procurarCompra(lista, tamanhoLista);
        }
        else{
            printf("opcao invalida\n");
        }
    }

    free(lista);
    return 0;
}


void inserirCompra(Compra **lista, int *tamanhoLista){
    *lista = (Compra *) realloc(*lista, (*tamanhoLista + 1) *sizeof(Compra));
    scanf("%s %f %d", (*lista)[*tamanhoLista].nome, &(*lista)[*tamanhoLista].valor, &(*lista)[*tamanhoLista].quantidade);
    (*tamanhoLista)++;
}

void removerCompra(Compra **lista, int *tamanhoLista){
    char produto[50];
    int qtd_remover;
    scanf("%s %d", produto, &qtd_remover);

    for (int i=0; i<*tamanhoLista; i++){
        if (strcmp((*lista)[i].nome, produto) == 0){
            (*lista)[i].quantidade = (*lista)[i].quantidade - qtd_remover;

            if((*lista)[i].quantidade <= 0){
                (*lista)[i] = (*lista)[*tamanhoLista - 1];
                *lista = (Compra *) realloc (*lista, (*tamanhoLista - 1) * sizeof(Compra));
                (*tamanhoLista)--;
            }
        }
    }
}

void removerGrupoCompra(Compra **lista, int *tamanhoLista){
    float valor = 0.0;

    scanf("%f", &valor);

    for(int i=0; i<*tamanhoLista; i++){
        if((*lista)[i].valor = valor){
            (*lista)[i] = (*lista)[*tamanhoLista - 1];
            *lista = (Compra *) realloc (*lista, (*tamanhoLista - 1) * sizeof(Compra));
            (*tamanhoLista)--;
        }
    }
}

void consultarLista(Compra *lista, int tamanhoLista){
    float valor = 0;
    for(int i=0; i<tamanhoLista; i++){
        valor = valor + (lista[i].quantidade * lista[i].valor);
    }
    printf("Atualmente o valor da lista de compra está em: %.1f\n\n", valor);
}

void procurarCompra(Compra *lista, int tamanhoLista){
    char produto[50];

    scanf(" %s", produto);

    if(tamanhoLista == 0){
        printf("%s nao encontrado.\n\n", produto);
        return;
    }
    for(int i=0; i<tamanhoLista; i++){
        if(strcmp(lista[i].nome, produto) ==0){
            printf("%s\n", lista[i].nome);
            printf("- %i\n", lista[i].quantidade);
            printf("- %.1f\n\n", lista[i].valor);
            return;
        }
    }
    
    printf("%s nao encontrado.\n\n", produto);

}