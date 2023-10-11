#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *file;
    //file = fopen("C:Users\\mayre_e0trsrx\\OneDrive\\Documentos\\Linguagem-C\\Arquivos\\Testes\\arq\\string.txt", "w");
    file = fopen("numeroo.txt", "w");

    if(file == NULL){
        printf("\n\nProblema em criar o arquivo\n\n\n");
        exit(1);
    }


    fprintf(file, "Novo arquivo\n");

    fclose(file);

    system("pause");
    return 0;
}