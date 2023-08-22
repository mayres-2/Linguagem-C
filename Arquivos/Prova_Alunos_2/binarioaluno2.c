#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *file = fopen("alunos.bin", "rb");
    if(file==NULL){
        printf("problema em criar arquivo\n");
        exit(1);
    }

    int i=0;
    fread(&i, sizeof(int), 1, file);
    printf("\n%i\n", i);
    
    char string[100];
    fread(string, sizeof(char), 100, file);
    string[strlen(string)] = '\0';
    printf("%s\n", string);
    
    fread(&i, sizeof(int), 1, file);
    printf("%i\n", i);

    float num[i];
    for(int j=0; j<i; j++){
        fwrite(&num[j], sizeof(float), 1, file);
        printf("%.2f, ", num[j]);
    }
    printf("\n\n");
    

    fclose(file);
    return 0;
}