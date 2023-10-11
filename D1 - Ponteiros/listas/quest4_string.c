#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void adicionar(char ***pStr, int *tam, char *str);
void mostraTudo(char **pStr, int tam);

int main(){
    char str[1000000];
    char **pStr = NULL;
    int escolha=-1;
    int tam=0;

    do {
        printf("=======MENU=======\n");
        printf("0. Sair\n");
        printf("1. Adcionar string\n");
        printf("2. Printar tudo\n");
        scanf("%d", &escolha);

        if(escolha==1){
            printf("Digite a nova string: "); 
            scanf(" %s", str);
            adicionar(&pStr, &tam, str);
        }
        else if(escolha==2){
            mostraTudo(pStr, tam);
        }
        else if(escolha==0){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invalida");
        }
        
    } while(escolha!=0);

    for(int i=0; i<tam; i++){
        free(pStr[i]);
    }
    free(pStr);

    return 0;
}

void adicionar(char ***pStr, int *tam, char *str){
    char **tmp = (*pStr);
    (*pStr) = (char **) realloc((*pStr), ((*tam)+1) * sizeof(char*));
    if((*pStr)== NULL){
        printf("Erro de alocacao\n");
        exit(1);
    }
    (*pStr)[*tam] = strdup(str);
    (*tam)++;
}


void mostraTudo(char **pStr, int tam){
    if(pStr==NULL){
        printf("Nao tem strings dentro do vetor\n");
        return;
    }
    else {
        for(int i=0; i<tam; i++){
            printf("%s\n", pStr[i]);
        }
        printf("\n");
        return;
    }
}
