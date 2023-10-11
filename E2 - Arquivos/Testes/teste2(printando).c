#include <stdio.h>
#include <stdlib.h>


int main (){
    FILE *file;
    file = fopen("string.txt", "r");

    if(file == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
        exit(1);
    }

    char frase[100];

    while(fgets(frase, 100, file) != NULL){
        printf("%s", frase);
    }
    printf("\n");
    fclose(file);
    
    return 0;
}