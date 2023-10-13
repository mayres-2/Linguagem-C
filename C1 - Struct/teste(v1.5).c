#include <stdio.h>
#include <string.h>

#define tam 110

typedef struct{
    char contas[10];
    int a, b, c;
    int entrada;
} Numeros;

int main (){
    Numeros numero[tam];
    int i=0, entrada=-1;

    do{
        
        printf("\n=-=-=-=-Menu-=-=-=-=\n");
        printf("1. Somar\n2. Subtrair\n3. Multiplicar\n4. Dividir\n5. Mostrar tudo\n6. Nada\n");

        //entrada
            scanf("%d", &entrada);
            numero[i].entrada = entrada;

            if(entrada>0 && entrada<5){
                printf("Dois numeros\n");
                scanf("%d", &numero[i].a); scanf("%d", &numero[i].b);
            }
        //

        //contas
            if(entrada==1){
                numero[i].c = numero[i].a + numero[i].b; 
                printf("%d\n", numero[i].c); 
                strcpy(numero[i].contas, "soma"); 
                i++; 
            }
            else if(entrada==2){
                numero[i].c = numero[i].a - numero[i].b; 
                printf("%d\n", (numero[i].a - numero[i].b)); 
                strcpy(numero[i].contas, "subtracao"); 
                i++; 
            }
            else if(entrada==3){
                numero[i].c = numero[i].a * numero[i].b; 
                printf("%d\n", numero[i].c); 
                strcpy(numero[i].contas, "produto"); 
                i++; 
            }
            else if(entrada==4){
                numero[i].c = numero[i].a/numero[i].b; 
                printf("%d\n", (numero[i].a/numero[i].b)); 
                strcpy(numero[i].contas, "quociente"); 
                i++; 
            }
        //

        //mostrando o que foi feito
            else if(entrada==5){ 
                for(int j=0; j<i; j++){ 
                    printf("%s:\n", numero[j].contas); 
                    printf("%d %c %d = %d\n", 
                            numero[j].a, 
                            (numero[j].entrada == 1 ? '+' : (numero[j].entrada == 2 ? '-' : (numero[j].entrada == 3 ? '*' : '/'))), 
                            numero[j].b, 
                            numero[j].c); 
                }
            }
        //

        //out
        else if(entrada==6){ printf("Saindo...\n"); }

        //ai nai
        else{ printf("invalido\n"); }

        //limite do nivel atual
        if(i==tam){ printf("Limite de memoria\n"); entrada = 6; }

    }while(entrada!=6);


    return 0;
}
