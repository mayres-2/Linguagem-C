#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// simulação do coppeliasim/vs vvvvv
#define simx_opmode_oneshot_wait 0
typedef float simxFloat;
typedef int simxInt;
simxInt simxSetJointTargetPosition(simxInt clientID, simxInt jointHandle, simxFloat targetPosition, simxInt operationMode);
void extApi_sleepMs(int time_ms);
// ^^^^^^^^

/*
extern "C" {
#include "extApi.h"
}
*/

void press_button(int clientID, int* joint_handlers, int button_index, simxFloat joint_positions[][6]);



int main(void)
{
    int clientID = 0;


    FILE* votos_arq = fopen("votos.txt", "r");
    char voto[16];
    char buffer;

    simxFloat joint_positions[][6] = {
        {0, 0, 0, 0, 0, 0}, //0
        {-18, -50, 10, -97.5, 20, 0}, //1
        {0, 0, 0, 0, 0, 0}, //2
        {0, 0, 0, 0, 0, 0}, //3
        {0, 0, 0, 0, 0, 0}, //4
        {0, 0, 0, 0, 0, 0}, //5
        {0, 0, 0, 0, 0, 0}, //6
        {0, 0, 0, 0, 0, 0}, //7
        {0, 0, 0, 0, 0, 0}, //8
        {0, 0, 0, 0, 0, 0}, //9
        {0, 0, 0, 0, 0, 0}, //BRANCO
        {0, 0, 0, 0, 0, 0}, //CORRIGE
        {0, 0, 0, 0, 0, 0}, //CONFIRMA
        {0, 0, 0, 0, 0, 0}, //PADRAO BASE //esse é só zero mesmo
        {22, -35, -10, -97.5, 15, 0}, //PADRAO TEMP
    };
    int joint_handlers[6] = {
        0, 0, 0, 0, 0, 0
    };



    //coloca cada joint na posicao padrao base
    for (int i = 0; i < 6; i++) {
        simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
        extApi_sleepMs(500);
    }
    //aguarda atuadores
    extApi_sleepMs(7000);



    //ate a ultima linha, recebe linha...
    int contador = 0;
    while (fgets(voto, 16, votos_arq)) {

        printf("voto %09i: ", contador);
        //coloca cada joint na posicao padrao temp
        for (int i = 0; i < 6; i++) {
            simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
            extApi_sleepMs(500);
        }
        //aguarda atuadores
        extApi_sleepMs(7000);

        int i;
        for (i = 0; voto[i] != '\n'; i++) {

            //... se houver numeros, os pressiona ...
            if (voto[i] >= '0' && voto[i] <= '9') {
                press_button(clientID, joint_handlers, voto[i] - '0', joint_positions);

                printf("%c", voto[i]);
            }
            else if (voto[i] == 'B') {
                //coloca cada joint na posicao BRANCO
                for (int i = 0; i < 6; i++) {
                    simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[10][i], simx_opmode_oneshot_wait);
                    extApi_sleepMs(500);
                }
                //aguarda atuadores
                extApi_sleepMs(7000);

                printf("B");
            }
            else if (voto[i] == 'X') {
                //coloca cada joint na posicao CORRIGE
                for (int i = 0; i < 6; i++) {
                    simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[11][i], simx_opmode_oneshot_wait);
                    extApi_sleepMs(500);
                }
                //aguarda atuadores
                extApi_sleepMs(7000);

                printf("X");
            }
        }

        //... e ao fim da linha ...

        //caso voto nao excluido, confirma
        if (i && (voto[i - 1] != 'X')) {
            //coloca cada joint na posicao cofirma
            for (int i = 0; i < 6; i++) {
                simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
                extApi_sleepMs(500);
            }
            //aguarda atuadores
            extApi_sleepMs(7000);
        }

        //coloca cada joint na posicao padrao base
        for (int i = 0; i < 6; i++) {
            simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
            extApi_sleepMs(500);
        }
        //aguarda atuadores
        extApi_sleepMs(7000);

        printf("\n");
        contador++;
    }
    //coloca cada joint na posicao padrao base
    for (int i = 0; i < 6; i++) {
        simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
        extApi_sleepMs(500);
    }
    //aguarda atuadores
    extApi_sleepMs(7000);
    printf("\n");


    fclose(votos_arq);

    return 0;
}



void press_button(int clientID, int* joint_handlers, int button_index, simxFloat joint_positions[][6])
{
    //coloca cada joint na posicao do botao selecionado
    for (int i = 0; i < 6; i++) {
        simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[button_index][i], simx_opmode_oneshot_wait);
        extApi_sleepMs(500);
    }
    //aguarda atuadores
    extApi_sleepMs(7000);

    //coloca cada joint na posicao padrao temp
    for (int i = 0; i < 6; i++) {
        simxSetJointTargetPosition(clientID, joint_handlers[i], joint_positions[13][i], simx_opmode_oneshot_wait);
        extApi_sleepMs(500);
    }
    //aguarda atuadores
    extApi_sleepMs(7000);
}










simxInt simxSetJointTargetPosition(simxInt clientID, simxInt jointHandle, simxFloat targetPosition, simxInt operationMode)
{
    //seta joint em jointhandle para targetposition
    //return simxint

}

void extApi_sleepMs(int time_ms)
{
    //esperar time_ms milisegundos
} 