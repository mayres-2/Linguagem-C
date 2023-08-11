
/*1. Declare uma variável do tipo char chamada c e um ponteiro para char chamado pc. Inicialize
c com o valor ‘a’ e pc com o endereço de c. Utilizando %p para endereços de memória, Imprima as
seguintes linhas
*/
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char c;
	char *pc = &c;

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

/*2. Declare um vetor de inteiros vet[5] = {1,2,3,4,5} e um ponteiro de inteiros p que aponte para esse
vetor. Imprima
*/
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

    //lê a string de apenas uma palavra

    //solução
    //comprimento da string
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
    /*4. Faça um programa que aloque dinamicamente um vetor de 
    strings str, receba de entrada várias strings enquanto 
    existir entrada no buffer e guarde-as nesse vetor utilizando 
    ponteiros auxiliares (ponteiro temporário na hora de dar realloc).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

int main() {
    char** str = NULL;
    int size = 0;
    int capacity = 0;

    printf("Digite as strings (Ctrl+D para encerrar):\n");

    while (1) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        char* temp = (char*)malloc(strlen(buffer) + 1);

        if (temp == NULL) {
            printf("Erro ao alocar memória\n");
            return 1;
        }

        strcpy(temp, buffer);

        if (size >= capacity) {
            capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
            char** new_str = (char**)realloc(str, capacity * sizeof(char*));

            if (new_str == NULL) {
                printf("Erro ao realocar memória\n");
                return 1;
            }

            str = new_str;
        }

        str[size] = temp;
        size++;
    }

    printf("\nStrings digitadas:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", str[i]);
        free(str[i]);
    }

    free(str);

    return 0;
}


    

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//