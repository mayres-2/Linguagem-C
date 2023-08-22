#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char nomeEl[50];
    char cpf[13];
} Eleitor;

typedef struct{
    char nomeCan[50];
    int numCan;
} Candidato;

typedef struct{
    Candidato *DeputadoFederal; //0
    Candidato *DeputadoEstadual; //1
    Candidato *Senador; //2
    Candidato *Governador; //3
    Candidato *Presidente; //4
    int qtd_Cand[5];
} listaCandidatos;

typedef struct{
    Candidato *nomeCanElegivel;
    int votos;
}TotalVoto;

listaCandidatos carregarCandidatos(char *nomeArq);
Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores);
int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt);
int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt);
void apresentaResultado(TotalVoto *votos, int qtdCandidatos);
Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo);


int main(){
    int escolha=-2;
    int qtd_Eleitores=0;
    bool encontrado=false;
    TotalVoto *votos;
    
    Eleitor comprado; Candidato vendido, *branco; char cargo[30];
    listaCandidatos listaC = carregarCandidatos("Candidatos.txt");
    Eleitor *listaE = carregarEleitores("Eleitores.txt", &qtd_Eleitores);
    if(listaE==NULL){
        printf("Galo voou\n");
        exit(1);
    }
    


    do{
        printf("---------------------\n");
        printf("(1)Votar\n");
        printf("(2)Apresentar Votacao\n");
        printf("(3)Sair.\n");
        printf("---------------------\n");

        scanf("%d", &escolha);

        if(escolha==1){

            int i=0;
            do{
                encontrado=false;

                printf("Dados do Eleitor\n");
                printf("Nome: \n"); scanf(" %49[^\n]", comprado.nomeEl);
                printf("CPF(apenas numeros): \n"); scanf(" %12[^\n]", comprado.cpf);
                if(verificaEleitor(listaE, comprado) == 1){
                    printf("Dados do Candidato\n");
                    printf("Cargo do Candidato: \n"); scanf(" %29[^\n]", cargo);
                    printf("Nome do Candidato: \n"); scanf(" %49[^\n]", vendido.nomeCan);
                    printf("Numero do Candidato: \n"); scanf(" %49[^\n]", vendido.numCan);
                    int k=-1;
                    if(verificaCandidato(listaC, vendido) == 1){
                        if(strcmp(cargo, "deputada federal")==0) { k=0; listaC.qtd_Cand[k]++;}
                        else if(strcmp(cargo, "depudata estadual")==0) { k=1; listaC.qtd_Cand[k]++;}
                        else if(strcmp(cargo, "senador")==0){ k=2; listaC.qtd_Cand[k]++;}
                        else if(strcmp(cargo, "governador")==0) { k=3; listaC.qtd_Cand[k]++;}
                        else if(strcmp(cargo, "presidente")==0) { k=4; listaC.qtd_Cand[k]++;}
                        else{
                            encontrado=false;
                        }

                        if(k!=-1){
                            for(int j=0; j<listaC.qtd_Cand[k] && encontrado==false; j++){
                                //verificar se ja existe em votos do TotalVotos
                                if(j) {
                                    encontrado=true;

                                }
                            }

                            votos[i].nomeCanElegivel = localizaCandidato(listaC, vendido, cargo);
                            votos[i].votos++;
                            i++;
                        }

                    }
                    else{
                        printf("Candidato nao encontrado\n");
                    }
                }
                else{
                    printf("Eleitor nao encontrado\n");
                }

            } while(strcmp(comprado.cpf,"-1") != 0);

            printf("Finalizada votacao\n");

        }
        else if(escolha==2){
            //faltando coisa//
            for(int i=0; i<5; i++){
                apresentaResultado(votos, listaC.qtd_Cand);
            }
            printf("Finalizada apresentacao\n");
        }
        else if(escolha==3){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invavalida\n");
        }

    }while(escolha!=3);


    
    return 0;
}


listaCandidatos carregarCandidatos(char *nomeArq){
    /**/
}

Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores){
    /**/
}

int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt){
    /**/
}

int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt){
    /**/
}

void apresentaResultado(TotalVoto *votos, int qtdCandidatos){
    /**/
}

Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo){
    /**/
}
