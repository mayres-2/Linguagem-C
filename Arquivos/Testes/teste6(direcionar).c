#include <stdio.h>
#include <stdlib.h>


int main(){
    char x[100];

    int i = 0;
    while((x[i] = fgetc(stdin) ) != '\n'){
        ++i;
    }
    //x[i] = '\0';
    x[++i] = '\0';

    //outra funcao
    int i=0;
    while((x[i] = getc(stdin)) != '\n'){
        ++i;
    }
    //x[i] = '\0';
    x[++i] = '\0';

    printf("%s", x);

    return 0;
}

///outra parada de char


int main(){
    char x[100];

    FILE *file = fopen("string.txt", "r");
    
    int i=0;
    while((x[i] = getc(file)) != EOF){
        ++i;
    }
    x[i] = '\0';

    printf("%s", x);

    fclose(file);
    
    return 0;
}