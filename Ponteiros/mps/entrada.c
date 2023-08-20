#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    int idade;
    float salario;
} Pessoa;

Pessoa *inserirPessoa(Pessoa *cidade, int tam);
void viewTable(Pessoa *cidade, int tam);


int main(){
    int choice = -1;
    int tam = 0;
    Pessoa *cidade = NULL;

    while(choice != 0){
        printf("========Menu========\n");
        printf("0. Sair\n");
        printf("1. Inserir Pessoa na Cidade\n");
        printf("2. Ver todas as pessoas da Cidade\n");
        scanf("%d", &choice);

        if(choice==0){
            printf("Saindo...\n");
        }
        else if(choice == 1){
            cidade = inserirPessoa(cidade, tam);
            tam++;
        }
        else if(choice == 2){
            viewTable(cidade, tam);
        }
    }
    

    free(cidade);
    return 0;
}

//latente//patente

Pessoa *inserirPessoa(Pessoa *cidade, int tam){
    Pessoa *tmp = cidade;
    cidade = (Pessoa *) realloc(cidade, (tam+1) * sizeof(Pessoa));
    if(cidade == NULL){
        printf("problema de aclocacao de memoria\n");
        free(tmp);
        exit(1);
    }

    printf("Nome: \n");
        getchar();
        /*
        fgets(cidade[tam].nome, sizeof(cidade[tam].nome), stdin);
        int i=0;
        while(i<strlen(cidade[tam].nome) && cidade[tam].nome[i] != '\n'){
            i++;
        } cidade[tam].nome[i++] = '\0';
        */
        fgets(cidade[tam].nome, sizeof(cidade[tam].nome), stdin);
        cidade[tam].nome[strlen(cidade[tam].nome)] = '\0';
    printf("Idade: \n"); scanf("%d", &cidade[tam].idade);
    printf("Salario: \n"); scanf("%f", &cidade[tam].salario);

    return cidade;
}

void viewTable(Pessoa *cidade, int tam){

    for(int i=0; i<tam; i++){
        printf("Nome: %s\n", cidade[i].nome);
        printf("Idade: %d\n", cidade[i].idade);
        printf("Salario: %.2f\n", cidade[i].salario);
    }
    printf("\n");
}