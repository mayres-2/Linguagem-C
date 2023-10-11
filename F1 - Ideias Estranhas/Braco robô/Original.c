#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "extApi.h"
}

int main(int argc, char* argv[])
{

    //variavei para handler das juntas
    int handler = 0;

    //conecta com o coppelia
    int clientID = simxStart((simxChar*) "127.0.0.1", 19999, true, true, 2000, 5);

    extApi_sleepMs(500);

    //verifica conexao com simulador
    if (clientID == -1) {
        printf("Erro conectando ao Coppelia!\n");
        return 0;
    } else {
        printf("Conectado ao Coppelia!\n");
    }
    
    //configura o handler da primeira junta
    simxChar handlerName[150] = "/NiryoOne/Joint";
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);
   
    for (int i = 1; i <= 6; i++) {

        printf("Testando junta %d\n", i);

        //move a junta ate seu ponto maximo
        simxSetJointTargetPosition(clientID, handler, (simxFloat) 0, (simxInt)simx_opmode_oneshot_wait);
        extApi_sleepMs(2000);
        simxSetJointTargetPosition(clientID, handler, (simxFloat) 2*PI, (simxInt)simx_opmode_oneshot_wait);
        extApi_sleepMs(2000);
        simxSetJointTargetPosition(clientID, handler, (simxFloat) 0, (simxInt)simx_opmode_oneshot_wait);

        //passa para a proxima junta
        strcat(handlerName, "/Link/Joint");
        simxGetObjectHandle(clientID, (simxChar*) handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    }
    
    // Fecha a conexao 
    simxFinish(clientID);

    return(0);
}
