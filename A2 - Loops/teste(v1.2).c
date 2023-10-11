#include <stdio.h>
#include <stdlib.h>


int main (){
    int a=0, b=9, c;
    int entrada=0;

    do{
        printf("=-=-=-=-Menu-=-=-=-=\n");
        printf("1. Somar\n2. Subtrair\n3. Multiplicar\n4. Dividir\n5. Nada\n");
        
        //entrada
            scanf("%d", &entrada);
            if(entrada>0 && entrada<5){
                printf("Dois números\n");
                scanf("%d", &a); scanf("%d", &b);
            }
        //

        if(entrada==1){ c = a + b; printf("%d\n", c); }
        else if(entrada==2){ printf("%d\n", (a - b)); }
        else if(entrada==3){ c = a * b; printf("%d\n", c); }
        else if(entrada==4){ printf("%d\n", (a/b)); }
        
        else if(entrada==5){ printf("Saindo...\n"); }
        else{ printf("invalido\n"); }

    }while(entrada!=5);

    return 0;
}
