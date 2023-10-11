#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char RG[11];
    char Nascimento[11];
    char Passagem[11];
    char DataPassagem[11];
    char Assento[4];
} Passageiros;


int main () {
    int N=0;

    //pessoas que chegarao
    scanf("%d", &N);
    Passageiros pessoas[N];

    for(int i=0; i<N; i++){
        scanf(" %10[^\n]", pessoas[i].RG);
        scanf(" %10[^\n]", pessoas[i].Nascimento);
        scanf(" %10[^\n]", pessoas[i].Passagem);
        scanf(" %10[^\n]", pessoas[i].DataPassagem);
        scanf(" %3[^\n]", pessoas[i].Assento);

        if(strcmp(pessoas[i].RG, "Nao possui") == 0){
            printf("a saida e nessa direção\n");
        }
        else {
            if(strcmp(pessoas[i].Passagem, "Nao possui") == 0){
                printf("a recepição e nessa direção\n");
            }
            else{
                if(strcmp(pessoas[i].DataPassagem, pessoas[i].Nascimento) != 0){
                    printf("190\n");
                }
                else{
                    printf("o seu assento e %s tenha um bom dia\n", pessoas[i].Assento);
                }     
            }
        }
    }


    return 0;
}

