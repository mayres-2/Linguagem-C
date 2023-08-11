#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> 

#define max 1000000000

//\\//\\//\\//\\//\\//\\//

typedef struct{
    char placa[6];
} Caminhao;

//\\//\\//\\//\\//\\//\\//

typedef struct{
    int codigo;
    float loc_x, loc_y;
    Caminhao *caminhao;
    int n_caminhao;
} Filial;

//\\//\\//\\//\\//\\//\\//

typedef struct{
    float origem_x, origem_y;
    float destino_x, destino_y;
} Produto;

//\\//\\//\\//\\//\\//\\//

Caminhao remover_caminhao(Filial *filiais, int codigo_filial);
Filial *cadastrar_filial(Filial *filiais, int *n_filiais);
void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial);
void realizar_entrega(Filial *filiais, Produto produto, int n_filiais);
void imprimir_filiais(Filial *filiais, int n_filiais);

//\\//\\//\\//\\//\\//\\////\\//\\//\\//\\//\\//\\////\\//\\//\\//\\//\\//\\//

int main(){
    int escolha=0, qtdfiliais=0;
    Filial *filial = NULL;
    Caminhao add;
    Produto new;

    do
    {
        printf("   ===============MENU===============\n");
        printf("\t1...Cadastrar filial\n");
        printf("\t2...Cadastrar caminhao\n");
        printf("\t3...Realizar entrega\n");
        printf("\t4...Imprimir filiais\n");
        printf("\t5...Sair\n");
        scanf("%d", &escolha);

        if(escolha==1){
            filial = cadastrar_filial(filial, &qtdfiliais);
        }
        else if(escolha==2){
            int index;
            printf("Qual o indice da filial que vai receber o caminhao? ");
            scanf("%d", &index);
            printf("Qual a placa do caminhao ? ");
            scanf(" %s", add.placa);
            cadastrar_caminhao(filial, add, index);

        }
        else if(escolha==3){
            printf("Qual a localizacao da origem do produto no eixo x? ");
            scanf("%f", &new.origem_x);
            printf("Qual a localizacao da origem do produto no eixo y? ");
            scanf("%f", &new.origem_y);
            printf("Qual a localizacao do destino do produto no eixo x? ");
            scanf("%f", &new.destino_x);
            printf("Qual a localizacao do destino do produto no eixo x? ");
            scanf("%f", &new.destino_y);
            realizar_entrega(filial, new, qtdfiliais);
        }
        else if(escolha==4){
            imprimir_filiais(filial, qtdfiliais);
        }
        else if(escolha==5){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invalida!\n");
        }

    } while(escolha!=5);

    for(int i=0; i<qtdfiliais; i++){
        free(filial[i].caminhao);
    }

    free(filial);

    return 0;
}

//\\//\\//\\//\\//\\//\\////\\//\\//\\//\\//\\//\\////\\//\\//\\//\\//\\//\\//

/////////menu//////////


void imprimir_filiais(Filial *filiais, int n_filiais){
    //a luta é grande, mas a derrota é certa :) Alves; Gabriel.
    
    //...
    if(filiais==NULL){
        printf("Nao temos filiais cadastradas ainda\n");
        return;
    }
    else if(n_filiais == 0){
        printf("Esse eh o codigo da filial: %d\n", filiais[n_filiais].codigo);
        if(filiais[n_filiais].caminhao==NULL){
            printf("  Nao temos caminhoes cadastrados nessa filial\n");
        }
        else if(filiais[n_filiais].n_caminhao == 0){
            printf(" Esse eh o numero de caminhoes: %d\n", filiais[n_filiais].n_caminhao);
            printf("  Placa do caminhao: %s\n", filiais[n_filiais].caminhao[0].placa);
        }
        else{
            printf(" Esse eh o numero de caminhoes: %d\n", filiais[n_filiais].n_caminhao);
            for(int j=0; j<filiais[n_filiais].n_caminhao; j++){
                printf("  Placa do caminhao: %s\n", filiais[n_filiais].caminhao[j].placa);
            }
        }
    }
    else {
        for(int i=0; i<n_filiais; i++){
            printf("Esse eh o codigo da filial: %d\n", filiais[i].codigo);
            if(filiais[i].caminhao==NULL){
                printf("  Nao temos caminhoes cadastrados nessa filial\n");
            }
            else if(filiais[i].n_caminhao == 0){
                printf(" Esse eh o numero de caminhoes: %d\n", filiais[i].n_caminhao);
                printf("  Placa do caminhao: %s\n", filiais[i].caminhao[0].placa);
            }
            else{
                printf(" Esse eh o numero de caminhoes: %d\n", filiais[i].n_caminhao);
                for(int j=0; j<filiais[i].n_caminhao; j++){
                    printf("  Placa do caminhao: %s\n", filiais[i].caminhao[j].placa);
                }
            }                                                                                            
        }
    }
}

//\\//\\//\\//\\//\\//\\//

Filial *cadastrar_filial(Filial *filiais, int *n_filiais){
    float locX, locY;
    printf("Qual a loc da nova filial no eixo X? ");   
    scanf("%f", &locX);
    printf("Qual a loc da nova filiao no eixo Y? ");
    scanf("%f", &locY);

    Filial *tmp = filiais;
    filiais = (Filial *) realloc (filiais, (*n_filiais + 1) * sizeof(Filial));

    if (filiais == NULL){
        printf("Erro de alocando memoria\n");
        for(int i=0; i<*n_filiais; i++){
            free(tmp[i].caminhao);
        }
        free(tmp);
        exit(1);
    }

    printf("\nFilial cadastrada com sucesso!\n");
    filiais[*n_filiais].loc_x = locX;
    filiais[*n_filiais].loc_y = locY;
    filiais[*n_filiais].codigo = *n_filiais;
    filiais[*n_filiais].n_caminhao = 0;
    filiais[*n_filiais].caminhao = NULL;
    (*n_filiais)++;
    return filiais;
}

//\\//\\//\\//\\//\\//\\//

void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial){
    Caminhao *tmp = filiais[codigo_filial].caminhao;
    filiais[codigo_filial].caminhao = (Caminhao *) realloc (filiais[codigo_filial].caminhao, (filiais[codigo_filial].n_caminhao + 1) * sizeof(Caminhao));
    if (filiais[codigo_filial].caminhao == NULL){
        printf("Erro\n");
        free(tmp);
        exit(1);
    }
    filiais[codigo_filial].caminhao[filiais[codigo_filial].n_caminhao] = caminhao;
    filiais[codigo_filial].n_caminhao++;
    printf("Caminhao cadastrado com sucesso!\n");
}

//\\//\\//\\//\\//\\//\\//

//problema na entrega
void realizar_entrega(Filial *filiais, Produto produto, int n_filiais){
    float DistOrigem, DistDestino;
    float minOrigem = max, minDestino = max;
    int indexOrigem = -1, indexDestino = -1;

    if(filiais==NULL){
        imprimir_filiais(filiais, n_filiais);
        return;
    }
    else if(n_filiais==0){
        DistOrigem = sqrt(pow(produto.origem_x - filiais[0].loc_x, 2) + pow(produto.origem_y - filiais[0].loc_y, 2));

            if(DistOrigem <minOrigem){
                if(filiais[0].n_caminhao > 1){
                    minOrigem = DistOrigem;
                    indexOrigem = 0;
                }
            }

            DistDestino = sqrt(pow(produto.destino_x - filiais[0].loc_x, 2) + pow(produto.destino_y - filiais[0].loc_y, 2));

            if(DistDestino < minDestino){
                minDestino = DistDestino;
                indexDestino = 0;
            }
    }
    else {
        for (int i=0; i<n_filiais; i++){
            DistOrigem = sqrt(pow(produto.origem_x - filiais[i].loc_x, 2) + pow(produto.origem_y - filiais[i].loc_y, 2));

            if(DistOrigem <minOrigem){
                if(filiais[i].n_caminhao > 1){
                    minOrigem = DistOrigem;
                    indexOrigem = i;
                }
            }

            DistDestino = sqrt(pow(produto.destino_x - filiais[i].loc_x, 2) + pow(produto.destino_y - filiais[i].loc_y, 2));

            if(DistDestino < minDestino){
                minDestino = DistDestino;
                indexDestino = i;
            }
        }
    }

    if(minOrigem == max || minDestino == max){
        printf("Nao foi possivel realizar a entrega por falta de filiais\n");
        return;
    }
    else{
        Caminhao add = remover_caminhao(filiais, indexDestino);
        cadastrar_caminhao(filiais, add, indexDestino);
        if(indexDestino == indexDestino){
            printf("A filial %d vai fazer a entrega!\n", filiais[indexDestino].codigo);
        }
        else{
            printf("O produto vai ir da filial %d até a filial %d para entrega do produto!\n", filiais[indexOrigem].codigo, filiais[indexDestino].codigo);
        }
    }

    return;
}

//\\//\\//\\//\\//\\//\\//

Caminhao remover_caminhao(Filial *filiais, int codigo_filial){
    Caminhao removido;
    strcpy(removido.placa, "sempl");
    if(filiais[codigo_filial].n_caminhao==0){
        printf("nao ha caminhoes nessa filial\n");
        return removido;
    }
    else{
        removido = filiais[codigo_filial].caminhao[filiais[codigo_filial].n_caminhao-1];
        filiais[codigo_filial].n_caminhao--;
        filiais[codigo_filial].caminhao = (Caminhao *) realloc(filiais[codigo_filial].caminhao, filiais[codigo_filial].n_caminhao * sizeof(Caminhao));
        return removido;   
    }
}