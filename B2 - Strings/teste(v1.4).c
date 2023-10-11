#include <stdio.h>
#include <string.h>

#define tam 110

int main (){
    int a[tam], b[tam], c[tam];
    int i=0, entrada[tam];
    char contas[tam][10];

    do{
        
        printf("\n=-=-=-=-Menu-=-=-=-=\n");
        printf("1. Somar\n2. Subtrair\n3. Multiplicar\n4. Dividir\n5. Mostrar tudo\n6. Nada\n");

        //entradas
            scanf("%d", &entrada[i]);

            if(entrada[i]>0 && entrada[i]<5){
                printf("Dois numeros\n");
                scanf("%d", &a[i]); scanf("%d", &b[i]);
            }
        //

        //contas
            if(entrada[i]==1){
                c[i] = a[i] + b[i]; 
                printf("%d\n", c[i]); 
                strcpy(contas[i], "soma"); 
                i++; 
            }
            else if(entrada[i]==2){
                c[i] = a[i] - b[i]; 
                printf("%d\n", (a[i] - b[i])); 
                strcpy(contas[i], "subtracao"); 
                i++; 
            }
            else if(entrada[i]==3){
                c[i] = a[i] * b[i]; 
                printf("%d\n", c[i]); 
                strcpy(contas[i], "produto"); 
                i++; 
            }
            else if(entrada[i]==4){
                c[i] = a[i]/b[i]; 
                printf("%d\n", (a[i]/b[i])); 
                strcpy(contas[i], "quociente"); 
                i++; 
            }
        //

        //mostrando o que foi feito
            else if(entrada[i]==5){ 
                for(int j=0; j<i; j++){ 
                    printf("%s:\n", contas[j]); 
                    printf("%d %c %d = %d\n", 
                            a[j], 
                            (entrada[j] == 1 ? '+' : (entrada[j] == 2 ? '-' : (entrada[j] == 3 ? '*' : '/'))), 
                            b[j], 
                            c[j]); 
                }
            }
        //

        //out
        else if(entrada[i]==6){ printf("Saindo...\n"); }

        //ai nai
        else{ printf("invalido\n"); }

        //limite do nivel atual
        if(i==tam){ printf("Limite de memoria\n"); entrada[i] = 6; }

    }while(entrada[i]!=6);


    return 0;
}
