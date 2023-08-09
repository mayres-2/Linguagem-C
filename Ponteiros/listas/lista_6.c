/*
1. Declare uma variável do tipo char chamada c e um ponteiro para char chamado pc. Inicialize
c com o valor ‘a’ e pc com o endereço de c. Utilizando %p para endereços de memória, Imprima as
seguintes linhas
*/

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

    //endereço do valor guardado no endereço apontado por pc
    printf("\nb)\n"); 
    printf("Endereco do valor guardado no endereco apontado por pc: %p\n", &*pc);
    printf("Endereco do ponteiro: %p\n", *&pc);

    /*

    explicação: 
        o '&' traz o endereco de determinada variavel,
        um ponteiro é um endereco de memoria, 
        para printar seu endereco nao basta escrever '&pc',
        pois ele aponta para o endereco dessa variavel dentro da memoria,
        e nele esta "guardado", apontando, o endereco de outra variavel, 
        e para mostrar o endereco apontado pelo ponteiro 
        '*' e '&' funcionam do mesmo jeito no print para ponteiro
    
    */



	return 0;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
    /*3. Usando somente as variáveis ptr_str, ptr_inv e i, complete o código abaixo para que ele que
inverta a string str e coloque na str_inv. (Não use o operador [ ] nem str e str_inv, utilize
somente os ponteiros e a aritmética de ponteiros)*/

/*

#include <stdio.h>
#include <string.h>

int main( ){
    char str[50]; // String
    char str_inv[50]; // String invertida
    char *ptr_str = str;
    char *ptr_inv = str_inv;
    int i=-1;
    scanf(" %s", str);
     //continue o código a partir daqui

    printf(" O inverso da string : %s\n\n",str_inv);

    return 0;
}

*/

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

    /*4. Faça um programa que aloque dinamicamente um vetor de strings str, receba de entrada várias
strings enquanto existir entrada no buffer e guarde-as nesse vetor utilizando ponteiros auxiliares 
(ponteiro temporário na hora de dar realloc).*/
    

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//