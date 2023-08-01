#include<stdio.h>

int main () {
    int escolha;
    int n=0, m=0;
    float resul=0;

    scanf("%d", &n);

    printf("O que você prefere?\n\t\t1. soma\n\t\t2. subtracao\n\t\t3. multiplicacao\n\t\t4. divisao\n");
    scanf("%d", &escolha);
    
    if(escolha>=1 && escolha<=4){
        scanf("%d", &m);
    }

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
        if(n!=0 || m!=0){
            if(n!=0) resul = m / n;
            else if(m!=0) resul = n / m;
        }
    }
    else {
        printf("Opcao nao eh valida\nTente de novo\n");
    }

    if(escolha>=1 && escolha<=4){
        printf("O resultado final é %i\n", resul);
    }

    return 0;
}