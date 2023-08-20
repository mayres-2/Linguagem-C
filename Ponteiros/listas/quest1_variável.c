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
