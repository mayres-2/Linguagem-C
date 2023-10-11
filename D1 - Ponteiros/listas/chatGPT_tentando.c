#include <stdio.h>
#include <stdlib.h>

int main() {
    int vet[5] = {1, 2, 3, 4, 5};
    int i=0;
    int *p = vet;// Ponteiro apontando para o vetor

    printf("a)\n");
    printf("Endereco guardado em vet: %p\n", &vet);
    printf("Endereco guardado em p: %p\n", &*p);

    printf("\nb)\n");
    for (i = 0; i < 5; i++) {
        printf("Valor (p) vet[%d]: %d\n", i, p[i]);
    }

    printf("\nc)\n");
    for (i = 0; i < 5; i++) {
        printf("Valor de (p) vet[%d]: %d\n", i, *(p + i));
    }

    printf("\nd)\n");
    for (i = 0; i < 5; i++) {
        printf("Valor de vet[%d]: %d\n", i, vet[i]);
    }
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf("Valor de vet[%d]: %d\n", i, *(vet + i));
    }

    return 0;
}
