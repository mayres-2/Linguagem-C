#include<stdio.h>

int main () {
    int escolha;
    int n=0, m=0;
    float resul=0;

    printf("Escolha um numero qualquer: ");
    scanf("%d", &n);

    printf("O que você prefere?\n\t1. soma\n\t2. subtracao\n\t3. multiplicacao\n\t4. divisao\n");
    scanf("%d", &escolha);
    
    if(escolha>=1 && escolha<=4){
        printf("Escolha outro numero qualquer: ");
        scanf("%d", &m);
        //calculando
        if(escolha == 1){
            resul = n + m;
        }
        else if(escolha == 2){
            resul = n - m;
        }
        else if(escolha == 3){
            resul = n * m;
        }
        else if(escolha == 4){
            resul = n / m;
        }
        //printando
        if(n!=0 || m!=0){
            printf("O resultado final eh %.0f\n", resul);
        }
        else if(n==0 && m==0){
            printf("O resultado final eh infinito\n");
        }
        else {
            printf("Nao sei\n");
        }
    }
    else {
        printf("Opcao nao eh valida\nTente de novo\n");
    }


    return 0;
}