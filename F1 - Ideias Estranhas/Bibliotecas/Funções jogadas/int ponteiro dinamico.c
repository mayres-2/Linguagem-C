#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void aumentar(int **pDuplo, int *tam);
void diminuir(int **pDuplo, int *tam);
void atualizar(int **pDuplo, int *tam);
void printar(int *pDuplo, int tam);

int main(){
    int *pDuplo=NULL;
    int tam=0;
    int escolha=-1;

    for(; escolha!=5;){
        printf("1. Aumentar\n");
        printf("2. Diminuir\n");
        printf("3. Atualizar dados\n");
        printf("4. Printar vetor\n");
        printf("5. Sair\n");
        scanf("%d", &escolha);

        if(escolha==1){
            aumentar(&pDuplo, &tam);
        }   
        else if(escolha==2){
            diminuir(&pDuplo, &tam);
        }
        else if(escolha==3){
            atualizar(&pDuplo, &tam);
        }
        else if(escolha==4){
            printar(pDuplo, tam);
        }
        else if(escolha==5){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invalida\n");
        }
    }


    return 0;
}

//
void aumentar(int **pDuplo, int *tam){
    int *tmp = (*pDuplo);
    *pDuplo = (int *) realloc(*pDuplo, ((*tam) + 1) * sizeof(int));
    if((*pDuplo) == NULL){
        printf("Erro de alocacao\n");
        free(pDuplo);
        exit(1);
    }
    printf("Digite o novo valor: ");
    scanf("%d", &(*pDuplo)[*tam]);
    (*tam)++;
}

//
void diminuir(int **pDuplo, int *tam){
    int num=0, index=0;
    int troca=0, escolha=0;
    bool encontrado = false;
    printf("Qual numero remover: "); scanf("%d", &num);

    for(int i=0; i<(*tam+1) && encontrado!=true; i++){
        if(num == (*pDuplo)[i]){
            encontrado = true;
            index = i;
        }
    }

    if(encontrado == false){
        printf("valor nao encontrado\n");
        return;
    }

    printf("\nTem certeza?\n(1)sim\n(2)nao\n");
    scanf("%d", &escolha);
    
    if(escolha==1){
        troca = (*pDuplo)[*tam-1];
        (*pDuplo)[*tam-1] = (*pDuplo)[index];
        (*pDuplo)[index] = troca;

        int *tmp = (*pDuplo);
        (*pDuplo) = (int *) realloc (*pDuplo, ((*tam) - 1) * sizeof(int));
        if((*pDuplo) == NULL){
            printf("Erro de alocacao\n");
            free(pDuplo);
            exit(1);
        }
        (*tam)--;
        printf("Valor mudado\n");
    }
    else if(escolha==2){
        printf("Ok...\n");
        return;
    }
    else {
        printf("opcao invalida\n");
        return;
    }

}

//
void atualizar(int **pDuplo, int *tam){
    int index=0, num=0;
    int escolha=0;
    bool encontrado=false;
    printf("Qual indice do vetor mudar? "); scanf("%d", &index);

    for(int i=0; i<(*tam+1) && encontrado!=true; i++){
        if(i == index){
            encontrado = true;
            printf("O que substituir? "); scanf("%d", &num);
            printf("O num trocado sera %d\nTem certeza \n(1)sim\n(2)nao\n", (*pDuplo)[i]);
            scanf("%d", &escolha);
            if(escolha==1){
                (*pDuplo)[i] = num;
                printf("Valor mudado\n");
                return;
            }
            else if(escolha == 2){
                printf("Ok..\n");
                return;
            }
            else {
                printf("Opcao invalida\n");
                return;
            }

        }
    }

    if(encontrado==false){
        printf("Valor nao encontrado\n");
        return;
    }
}

//
void printar(int *pDuplo, int tam){
    if(pDuplo==NULL){
        printf("Nao tem valor dentro desse vetor\n");
        return;
    }
    else {
        for(int i=0; i<tam; i++){
            printf("%d ", pDuplo[i]);
        }
        printf("\n");
        return;
    }
}