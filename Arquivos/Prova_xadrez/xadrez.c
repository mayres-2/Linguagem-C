#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
    /* data */
}nothing;

void printTabuleiro(char tab[8][8][2]);
bool checkmateKING(char tab[8][8][2]);
bool checkKING(char tab[8][8][2]);
bool verificaJogada(char jogada[7]);
//void moverPeca(char ****tab, char jogada[7]);
//bool verificarArqTabuleiro(char ****tab);

int main(){
    bool check=false, checkmate=false;
    bool player1B = true, player2P = false;
    int qtd_jogadas=0; char jogada[7];
    char jogador[2][8] = {
        "brancas", "pretas"
    };
    char tab[8][8][2] = {
        //a////b////c////d////e////f////g////h//
        {"T", "C", "B", "D", "R", "B", "C", "T"}, //8
        {"P", "P", "P", "P", "P", "P", "P", "P"}, //7
        {" ", " ", " ", " ", " ", " ", " ", " "}, //4
        {" ", " ", " ", " ", " ", " ", " ", " "}, //6
        {" ", " ", " ", " ", " ", " ", " ", " "}, //5
        {" ", " ", " ", " ", " ", " ", " ", " "}, //3
        {"p", "p", "p", "p", "p", "p", "p", "p"}, //2
        {"t", "c", "b", "d", "r", "b", "c", "t"}  //1
    };


    qtd_jogadas++;
    bool i=0;
    do{
        //verificarArqTabuleiro(&tab);
        ////""""MENU GERAL""""////
        printf("Jogo de Xadrez\n");
        if(qtd_jogadas%2!=0){ i = 0; }
        else{ i = 1; }
        printf("Vez do jogador das pecas %s\n", jogador[i]);
        printTabuleiro(tab);
        printf("Qual sua jogada? "); scanf(" %6[^\n] ", jogada);

        if (verificaJogada(jogada)){
            qtd_jogadas++;
            printf("ok\n");
        } else{
            printf("Jogada invalida\n");
        }

        //moverPeca(&tab, jogada);

        checkmate = checkmateKING(tab);

        //if(!checkmate){ check = checkKING(tab); }

    } while(checkmate!=true);
    
    printf("Fim de jogo\n");

    if(player1B == player2P){ printf("Empate\n"); }
    else if(player1B){ printf("Jogador 1 venceu\n"); }
    else if(player2P){ printf("Jogador 2 venceu\n"); }
    else{ printf("idk what happen\n"); }

    return 0;
}

//ok//
void printTabuleiro(char tab[8][8][2]){
    printf("--------------------------\n");
    for(int i=0; i<8; i++){
        printf("| ");
        for(int j=0; j<8; j++){
            printf("%s", tab[i][j]);
            printf(" ");
        }
        printf("|\n");
    }
    printf("--------------------------\n");
    system("clear");
}

//fazer//verifica se o rei esta em cheque mate
bool checkmateKING(char tab[8][8][2]){

    return false;

    return true;
}

//fazer
bool verificaJogada(char jogada[7]){
    char moves[8][8][4] = {
        //a/////b/////c/////d/////e/////f/////g/////h//
        {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"}, //8
        {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"}, //7
        {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"}, //6
        {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"}, //5
        {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"}, //4
        {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"}, //3
        {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"}, //2
        {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}  //1
    };
    /**/
    return true;
    return false;
}

//fazer
/*
void moverPeca(char ****tab, char jogada[7]){
    char peca;
    return;
}
*/

//fazer
/*
bool verificarArqTabuleiro(char ****tab){
    
    return 0;
}
*/
