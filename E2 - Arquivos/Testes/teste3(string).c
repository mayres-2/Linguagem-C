#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *file;
    file = fopen("string.txt", "a");

    if(file==NULL){
        printf("Arquivo nao pode ser aberto\n");
        getchar();
        exit(1);
    }

    //jeito 1
    fprintf(file, "\n");
    fprintf(file, "Primeira Linha\n");

    //jeito 2
    char frase[] = "Segunda Linha\n";
    fputs(frase, file);

    //jeito 3
    char caractere = '3';
    fputc(caractere, file);

    fprintf(file, "\n");
    
    printf("feito ein\n");
    
    fclose(file);
    
    system("pause");

    return 0;
}