#include <stdio.h>

#define myage 19
#define me '?'

int main(){
    //printf("%i%c\n", myage, me);
    int chute=0, idade=0;
    printf("           Hello, I'm Mayres :)\n");
    printf("         How old you think i am?\n");
    
    
    while(chute!=19){
        scanf("%d", &chute);
        if(chute<19){
            if(chute<=0){
                printf("                  ...\n");
                printf("\n          The guess was wrong.\n");
                printf("                I exist.\n");
            }
            else if(chute>0 && chute<=5){
                printf("             I build this!!\n");
                printf("           You can try again\n");
            }
            else if(chute>5 && chute<=17){
                printf("      I think you shold try again\n");
            }
            else if(chute==18){
                printf("         Maybe another guess\n");
            }
        }
        else if(chute>=20){
            if(chute==20 || chute==21 || chute==22){
                printf("          I'm close to that\n");
                printf("         Maybe another guess\n");
            }
            else if(chute>20 && chute<=70){
                printf("      I think you shold try again\n");
            }
            else if(chute>70 && chute<230){
                printf("  My grandmom and grandpa will be proud\n"
                        "        if i come to that age\n"
                        "         You shoul try again\n");
            }
            else if(chute>=230){
                printf("                  ...\n"
                        "        If i come to that age\n"
                        "    I'll wonder what should i do now\n"
                        "    Maybe I allready tryed everything\n"
                        "       I guess I'll wait to know\n"
                        "        And you shoul try again\n");
            }
        }
        else {
            for (int i=1; i<=chute; i++){
                for(int j=1; j<=12; j++){
                    for(int k=1; k<=30; k++){
                        idade += 1;
                    }
                }
            }
            printf("\n      I have close to %d days lived.\n", idade);
            printf("\n  I'm happy to know that i can be included\n"
                    "      by something so big how apple\n"
                    "        and so many things wait me\n"
                    "in this journey to know how, when and with who\n"
                    "       i'm gonna build a bumblebee.\n"
                    "                   <3\n"
                    "           can't wait for it.\n");
        }
    }
    return 0;
}