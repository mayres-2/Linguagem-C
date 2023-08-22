#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
	int ID_produto;
	int qtd;
	int preco;
} Produto;

void NEW(Produto **infoBase, int *n_produtos);
void RM(Produto **infoBase, int *n_produtos, int *prod);
void END(Produto **infoBase, int *n_produtos);

int main() {
	Produto *infoBase=NULL;
    int n_produtos=0;
    int algo_n=0;
	int escolha=-1;
	int prod=0;
	
	do{
		printf("========Menu========\n");
		printf("1. Adcionar produto\n");
		printf("2. Remover produto\n");
		printf("3. Finalizar compra\n"); //e ordenar
		scanf("%d", &escolha);
		
		if(escolha==1){
		    algo_n++;
            NEW(&infoBase, &n_produtos);
		}
        else if(escolha==2){
            printf("ID do produto que deseja remover? "); scanf("%d", &prod);
            RM(&infoBase, &n_produtos, &prod);
        }
        else if(escolha==3){
            END(&infoBase, &n_produtos);
        }
        else {
            printf("Opcao invalida\n");
        }
        n_produtos = algo_n;

	} while(escolha!=3); 
	

	free(infoBase);
	return 0;
}


void NEW (Produto **infoBase, int *n_produtos){
    Produto *tmp = (*infoBase);
    int num=0;
    (*infoBase) = (Produto *) realloc(*infoBase, ((*n_produtos)+1) * sizeof(Produto));
    if(*infoBase==NULL){
        printf("Erro de alocacao\n");
        free(tmp);
        exit(1);
    }

    printf("\nID do produto: "); scanf("%d", &num);
    (*infoBase)[*n_produtos].ID_produto = num;
    printf("\nQuantidade do procuto: "); scanf("%d", &num);
    (*infoBase)[*n_produtos].qtd = num;
    printf("\nPreco do produto: "); scanf("%d", &num);
    (*infoBase)[*n_produtos].preco = num;
    printf("\nProduto cadastrado\n");
    (*n_produtos)++;
    return;
}


void RM (Produto **infoBase, int *n_produtos, int *prod){
    Produto removido;
    bool encontrado = false;
    int index=0;
    
    for(int i=0; i<*n_produtos && encontrado==false; i++){
        if((*infoBase)[i].ID_produto == *prod){
            encontrado = true;
            index = i;
        }
    }
    
    if(encontrado==false){
        printf("Objeto nao encontrado\n");
        return;
    }
    else{
        //mudanca para a ultima posicao
        removido = (*infoBase)[index];
        (*infoBase)[index] = (*infoBase)[*n_produtos-1];
        (*infoBase)[*n_produtos-1] = removido;
    
        Produto *tmp = *infoBase;
        *infoBase = (Produto *) realloc(*infoBase, ((*n_produtos)-1)*sizeof(Produto));
        printf("Valor removido\n");
        if(*infoBase==NULL){
            printf("Erro de realocacao\n");
            free(tmp);
            exit(1);
            (*n_produtos)--;
            return;
        }
    }
}

//printar tudo
void END(Produto **infoBase, int *n_produtos){

    //ordenando
    for(int i=0; i<*n_produtos; i++){
        for(int j=0; j<*n_produtos - 1 - i; j++){
            if((*infoBase)[j].ID_produto > (*infoBase)[j+1].ID_produto){
                Produto tmp = (*infoBase)[j+1];
                (*infoBase)[j+1] = (*infoBase)[j];
                (*infoBase)[j] = tmp;
            }
        }
    }
    
    if(infoBase==NULL){
        printf("Nao tem nenhum produto cadastrado\n");
        return;
    }
    else{
        int total=0;
        printf("\nNota fiscal\n");
        for(int i=0; i<*n_produtos; i++){
            printf("ID do produto: %d\n", (*infoBase)[i].ID_produto);
            printf("Quatidade do produto: %d\n", (*infoBase)[i].qtd);
            printf("Preco de 1 produto: %d\nPreco total do produto: %d\n", (*infoBase)[i].preco, (*infoBase)[i].qtd * (*infoBase)[i].preco);
            total += ((*infoBase)[i].qtd) * ((*infoBase)[i].preco);
            printf("\n");
        }
        printf("Total da nota fiscal: %d\n", total);
        return;
    }

}
