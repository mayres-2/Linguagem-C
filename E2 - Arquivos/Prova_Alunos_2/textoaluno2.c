#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *file = fopen("alunos.txt", "w");
    if(file==NULL){
        printf("problema em criar arquivo\n");
        exit(1);
    }
    
    char string[100];
    scanf(" %[^\n]", string);
    printf("%s\n", string);
    fprintf(file, "%s, ", string);

    scanf(" %[^\n]", string);
    printf("%s\n", string);
    fprintf(file, "%s\n", string);
    

    fclose(file);
    return 0;
}