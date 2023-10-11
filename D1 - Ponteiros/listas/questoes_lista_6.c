
/*1. Declare uma variável*/
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char c;
	char *pc = NULL;

    pc = &c;

    c = 'a';

    printf("primeira questao\n");
    //endereço de c
    //valor guardado por ele
    printf("a)\n");
    printf("Endereco de c: %p\n", &c);
    printf("Valor de c: %c\n", c);
    printf("Valor de c: %d\n", c);

    //endereço de pc
    printf("\nb)\n"); 
    printf("Valor de pc: %c\n", *pc);
    printf("Valor de pc: %d\n", *pc);

    //e o valor guardado no endereço de pc
    printf("\nc)\n"); 
    printf("o endereco de pc: %p\n", &pc);
    //&pc nao mostra exatamente o endereço de c
    printf("o endereco de pc: %p\n", *pc);
    //*pc nao mostra exatamente o endereço de c

    //endereço do valor guardado no endereço apontado por pc
    printf("\nb)\n"); 
    printf("Endereco do valor guardado no endereco apontado por pc: %p\n", &*pc);
    printf("Endereco do ponteiro: %p\n", *&pc);

    free(pc);
	return 0;
}
*/
    /*
    explicação: 
        o '&' traz o endereco de determinada variavel,
        um ponteiro é um endereco de memoria, 
        para printar seu endereco nao basta escrever '&pc',
        pois ele aponta para o endereco dessa variavel dentro da memoria,
        e nele esta "guardado", apontando, o endereco de outra variavel, 
        e para mostrar o endereco apontado pelo ponteiro 
        '*' e '&' funcionam do mesmo jeito no print para ponteiro
        (APENAS QUANDO JUNTOS PARA A MESMA FUNCAO).
    */


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/*2. Declare um vetor*/
/*

#include <stdio.h>
#include <stdlib.h>

int main (){
    int vet[5] = {1,2,3,4,5};
    int *p = vet;

    printf("a)\n");
    printf("Endereco guardado em vet: %p\n", &vet);
    printf("Endereco guardado em p: %p\n", &*p);

    printf("\nb)\n");
    for(int i=0; i<5; i++){
        printf("Valor (p) vet[%d]: %d\n", i+1, p[i]);
    }

    printf("\nc)\n");
    for(int i=0; i<5; i++){
        printf("Valor de (p)vet[%d]: %d\n", i+1, *(p+i));
    }

    printf("\nd)\n");
    for(int i=0; i<5; i++){
        printf("Valor de vet[%d]: %d\n", i+1, vet[i]);
    }
    printf("\n");
    for(int i=0; i<5; i++){
        printf("Valor de vet[%d]: %d\n", i+1, *(vet+i));
    }

    return 0;
}

*/


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/*3. Usando somente as variáveis ptr_str, ptr_inv e i, complete o código abaixo para que ele que
inverta a string str e coloque na str_inv. (Não use o operador [ ] nem str e str_inv, utilize
somente os ponteiros e a aritmética de ponteiros)*/
/*

#include <stdio.h>
#include <string.h>


int main() {
    char str[50]; // String
    char str_inv[50]; // String invertida
    char *ptr_str = str;
    char *ptr_inv = str_inv;
    int i = -1;
    scanf(" %s", str);

    //solução
    while (*ptr_str != '\0') {
        ptr_str++;
        i++;
    }
    //ptr_str já está apontando para o último caractere (o nulo) da string original

    //string sendo invertida
    while (i >= 0) {
        ptr_str--;
        *ptr_inv = *ptr_str;
        ptr_inv++;
        i--;
    }
    
    *ptr_inv = '\0'; //caracter nulo no final para printar

    //saída
    printf(" O inverso da string : %s\n\n", str_inv);


    return 0;
}
*/


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
/*4. strings*/
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void adicionar(char ***pStr, int *tam, char *str);
void mostraTudo(char **pStr, int tam);

int main(){
    char str[1000000];
    char **pStr = NULL;
    int tam=0;

    while(scanf(" %s", str) != EOF) {

        scanf(" %s", str);
        
        adicionar(&pStr, &tam, str);

    } 

    mostraTudo(pStr, tam);

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
        free(tmp);
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

*/
    

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/*5.funcoes com ponteiros*/
/*
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
*/
