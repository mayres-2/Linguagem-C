#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "extApi.h"
}



/*
Funcao que lida com o aperto de um botao button_index
Com a martriz de coordenadas joint_positions
E esperando wait milisegundos
*/
void set_arm_position(int clientID, int* joint_handlers, int button_index, simxFloat joint_positions[][6], int wait);
void press_button(int clientID, simxInt* joint_handlers, int button_index, simxFloat joint_positions[][6]);



int main(int argc, char* argv[])
{
    /*
    // Tenta abrir arquivo de votos
    FILE* votos_arq = fopen("votos.txt", "r");

    // Verifica se aquivo foi aberto corretamente
    if (votos_arq == NULL) {
        printf("Erro ao abrir arquivo de votos!\n");
        return 404;
    }
    else {
        printf("Aberto arquivo de votos!\n");
    }
      */


    // Tenta conectar com o coppelia
    int clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 2000, 5);

    extApi_sleepMs(500);

    // Verifica conexao com simulador
    if (clientID == -1) {
        printf("Erro conectando ao Coppelia!\n");
        return 0;
    }
    else {
        printf("Conectado ao Coppelia!\n");
    }



    // Configura o handler para cada junta do robô em um vetor joint_handlers
    simxInt joint_handlers[6];
    simxChar handler_name[64] = "/base_link_respondable[0]/joint_ ";
    for (int i = 0; i < 6; i++) {
        sprintf(handler_name, "/base_link_respondable[0]/joint_%i", i + 1);
        simxGetObjectHandle(clientID, handler_name, &joint_handlers[i], (simxInt)simx_opmode_oneshot_wait);
    }



    /*
    convertendo valores de graus pra radianas
    ex repetitivos de valores pra usar no copia e cola:
    pode adicionar exemplos se quiser

            0: +0.000000
        -97.5: -1.701696
           10: +0.174533
           18: +0.314159

           60: +1.047200

    */

    // Matriz de valores que representa as coordenadas de cada joint em radianas para cada botão
    simxFloat joint_positions[][6] = {
        {-0.401425, -0.872664, -0.017453, -1.701696, +0.261799, +0.000000}, //0
        {-0.314159, -0.872665, +0.174533, -1.701696, +0.349066, +0.000000}, //1
        {-0.383972, -0.90355695, +0.2181662, -1.701696, +0.349066, +0.000000}, //2
        {-0.418879, -0.912458, 0.244346, -1.701696, +0.261799, +0.000000}, //3
        {-0.314159, -0.8464847, +0.0698132, -1.701696, +0.261799, +0.000000}, //4
        {-0.3700098, -0.872665, +0.113446, -1.701696, +0.261799, +0.000000}, //5
        {-0.418879, -0.890118, +0.139626, -1.701696, +0.261799, +0.000000}, //6
        {-0.314159, -0.837758, +0.00174533, -1.701696, +0.261799, +0.000000}, //7
        {-0.383972, -0.872665, +0.0523599, -1.701696, +0.261799, +0.000000}, //8
        {-0.453785, -0.900589, 0.095993, -1.701696, +0.261799, +0.000000}, //9
        {-0.331612558, -0.846484687, -0.130899694, -1.701696, +0.261799, +0.000000}, //10 BRANCO
        {-0.418879f, -0.8813913f, -0.0698132f, -1.701696f, +0.261799f, +0.000000f}, //11 CORRIGE
        {-0.511381, -0.935496, 0.017453, -1.701696, +0.261799, +0.000000}, //12 CONFIRMA
        {+0.000000, +0.000000, +0.000000, +0.000000, +0.000000, +0.000000}, //13 PADRAO BASE //esse é só zero mesmo
        {-0.383972, -0.610865, -0.174533, -1.701696, +0.261799, +0.000000}, //14 PADRAO TEMP

        //abaixo estao as coordenadas dos valores temp temp de cada botao
        //basicamente uma posicao acima do botao que a mao fica pra apertar so abaixando, 
        //sem colidir com outros botoes

        {-0.418879, -0.750492, -0.139626, -1.701696, +0.261799, +0.000000}, //0 + 15 (15) temp do 0
        {-0.314159, -0.802851, +0.174533, -1.701696, +0.349066, +0.000000}, //1 + 15 (16) temp do 1
        {-0.383972, -0.750492, +0.0872665, -1.701696, +0.349066, +0.000000}, //2 + 15 (17) temp do 2
        {-0.418879, -0.767945, +0.0872665, -1.701696, +0.261799, +0.000000}, //3 + 15 (18) temp do 3
        {-0.314159, -0.715584993, -0.0523598776, -1.701696, +0.261799, +0.000000}, //4 + 15 (19) temp do 4
        {-0.3700098, -0.733038286, -0.0174532925, -1.701696, +0.261799, +0.000000}, //5 + 15 (20) temp do 5
        {-0.453785606, -0.750491579, 0.01745329, -1.701696, +0.261799, +0.000000}, //6 + 15 (21) temp do 6 
        {-0.34906585, -0.698131701, -0.104719755, -1.701696, +0.261799, +0.000000}, //7 + 15 (22) temp do 7 
        {-0.436332f, -0.7504915f, -0.06981317f, -1.701696f, +0.349066f, +0.000000f}, //8 + 15 (23) temp do 8 
        {-0.488692f, -0.767945f, -0.04031711f, -1.701696f, +0.349066f, +0.000000f}, //9 + 15 (24) temp do 9 
        {-0.34906585, -0.698131701, -0.244346095, -1.701696, +0.349066, +0.000000}, //10 + 15 (25) temp do BRANCO

        {-0.445058959, -0.698131701, -0.244346095, -1.701696, +0.349066, +0.000000}, //11 + 15 (26) temp do CORRIGE
        {-0.523598776, -0.802851456, -0.104719755, -1.701696, +0.349066, +0.000000} //12 + 15 (27) temp do CONFIRMA
    };



        /*
    //le votos do arquivo, enviando-os como instrucoes para o braco
    char voto[32];
    int contador = 0;

    //ate a ultima linha, recebe linha...
    while (fgets(voto, 32, votos_arq)) {

        printf("voto %09i: %s", contador, voto);
        //seta braco na posicao temporaria geral
        set_arm_position(clientID, joint_handlers, 14, joint_positions, 10000);

        //loop ao longo do voto
        int i;
        for (i = 0; voto[i] != '\n'; i++) {

            //... se houver numeros, os pressiona ...
            if (voto[i] >= '0' && voto[i] <= '9') {

                press_button(clientID, joint_handlers, voto[i] - '0', joint_positions);
                printf("%c apertado\n", voto[i]);

            }
            //... se B, preciona branco
            else if (voto[i] == 'B') {

                press_button(clientID, joint_handlers, 10, joint_positions);
                printf("B apertado\n");

            }
            //e, se X, prerciona corrige
            else if (voto[i] == 'X') {

                press_button(clientID, joint_handlers, 11, joint_positions);
                printf("X apertado\n");

            }
        }

        //... e ao fim da linha ...

        //caso voto nao excluido, confirma
        if (i && (voto[i - 1] != 'X')) {

            press_button(clientID, joint_handlers, 12, joint_positions);
            printf("CONFIRMA apertado\n");

        }

        //retorna braco a posicao nula
        set_arm_position(clientID, joint_handlers, 13, joint_positions, 10000);

        printf("\n\n\n");
        contador++;
    }

    //retorna braco a posicao nula
    set_arm_position(clientID, joint_handlers, 13, joint_positions, 10000);
    printf("\n");


          */
    
    //testando todos os botoes

    //seta braco na base
    set_arm_position(clientID, joint_handlers, 13, joint_positions, 7000);

    for(int i = 8; i <= 12; i++) {

      //seta braco na posicao temporaria geral
      set_arm_position(clientID, joint_handlers, 14, joint_positions, 5000);

      //seta braco num botao
      set_arm_position(clientID, joint_handlers, i, joint_positions, 3000);

      press_button(clientID, joint_handlers, i, joint_positions);
      /*
      //seta braco na posicao temporaria geral
      set_arm_position(clientID, joint_handlers, 14, joint_positions, 5000);


      //temp desse botao
      set_arm_position(clientID, joint_handlers, i + 15, joint_positions, 3000);

      //seta braco num botao
      set_arm_position(clientID, joint_handlers,   i, joint_positions, 3000);

      //temp desse botao
      set_arm_position(clientID, joint_handlers, i + 15, joint_positions, 3000);
      */

    }

//seta braco na posicao temporaria
set_arm_position(clientID, joint_handlers, 14, joint_positions, 7000);

//seta braco na base
set_arm_position(clientID, joint_handlers, 13, joint_positions, 7000);





/*
//testando botao 2
set_arm_position(clientID, joint_handlers, 14, joint_positions, 7000);

set_arm_position(clientID, joint_handlers, 2 + 15, joint_positions, 3000);
set_arm_position(clientID, joint_handlers,  2, joint_positions, 3000);
set_arm_position(clientID, joint_handlers, 2 + 15, joint_positions, 3000);

set_arm_position(clientID, joint_handlers, 14, joint_positions, 3000);
set_arm_position(clientID, joint_handlers, 13, joint_positions, 7000);
*/


// Fecha arquivo de votos
//fclose(votos_arq);

// Fecha a conexao 
simxFinish(clientID);

//le fin
return(0);

}



/*
Funcao que lida com o aperto de um botao button_index
Com a martriz de coordenadas joint_positions
E esperando wait milisegundos
*/
void set_arm_position(int clientID, simxInt* joint_handlers, int button_index, simxFloat joint_positions[][6], int wait)
{

    printf("Colocando braco em posicao %i\n", button_index);

    // Coloca cada joint na posicao do botao selecionado
    for (int i = 0; i < 6; i++) {

        simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[button_index][i], simx_opmode_oneshot_wait);
        //extApi_sleepMs(500);

    }

    // Aguarda atuadores
    extApi_sleepMs(wait);

    return;

}

//aperta botao. parte da posicao temp
void press_button(int clientID, simxInt* joint_handlers, int button_index, simxFloat joint_positions[][6])
{
    //seta braco na posicao temp do numero
    set_arm_position(clientID, joint_handlers, button_index + 15, joint_positions, 2000);
    //seta braco no numero
    set_arm_position(clientID, joint_handlers, button_index, joint_positions, 2500);
    //seta braco na posicao tetmp do numero
    set_arm_position(clientID, joint_handlers, button_index + 15, joint_positions, 2000);

    //seta braco na posicao temp
    set_arm_position(clientID, joint_handlers, 14, joint_positions, 2000);
}