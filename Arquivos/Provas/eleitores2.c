/*
    Prova IP-EC
    Data: 19/09/2022
    Aluno: Felipe Ferreira da Silva Santos(ffss)
    Professor: ACM
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[110];
    int numero;
}Candidato;
typedef struct{
    Candidato *dep_estadual;
    Candidato *dep_federal;
    Candidato *senador;
    Candidato *governador;
    Candidato *presidente;

    int qtdCandidatos[5];
    
}listaCandidatos;

typedef struct{
    char nome[110];
    char cpf[11];
}Eleitor;

typedef struct{
    Candidato *apontaProCandidato;
    int totalDeVotos;
}TotalVoto;

listaCandidatos carregarCandidatos(char *nomeArq);
Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores);
int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt);
int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt, int qtdEleitores);
void apresentaResultado(TotalVoto *votos, int qtdCandidatos);
Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo);

int main(){
    //Build do sistema
    int qtdEleitores=0;
    listaCandidatos candidatos = carregarCandidatos("candidatos.txt");
    Eleitor *eleitores = carregarEleitores("eleitores.txt", &qtdEleitores);

    int i, j, qtdCandidatos=0;
    for(i=0;i<5;i++) qtdCandidatos+=candidatos.qtdCandidatos[5];

    //Sistema
    printf("-------------ELEIÇÃO 2022----------\n");
    char cpf[11];
    char nome[110];
    
    Eleitor tmp;
    Candidato candidato_tmp;
    Candidato *candidato_votado;
    int numero_voto;
    char cargos[5][110] = {"Deputada(o) federal", "Deputada(o) estadual", "Senador(a)", "Governador(a)", "Presidente"};
    
    TotalVoto pUmCandidato;
    TotalVoto votos[qtdCandidatos];//marcondes disse que pode ser fixo e que o senhor não iria tirar ponto
    int idx_votos=0;//"aponta para o estado da lista votos"
    int flag_computou;

    //inicializa os votos antes da votação
    for(i=0;i<qtdCandidatos;i++) votos[i].totalDeVotos=0;
    do{
        printf("Eleitor Informe o seu CPF.: ");
        scanf(" %s", cpf);
        if(strcmp(cpf, "-1")!=0){
            printf("Eleitor informe o seu Nome.: ");
            scanf(" %s", nome);

            strcpy(tmp.nome, nome);
            strcpy(tmp.cpf, cpf);
        
            if(verificaEleitor(eleitores, tmp, qtdEleitores)){
                for(i=0;i<5;i++){
                    printf("\t- Informe o seu número para %s.: ", cargos[i]);
                    scanf("%d", &numero_voto);

                    candidato_tmp.numero = numero_voto;
                    if(verificaCandidato(candidatos, candidato_tmp)){
                        candidato_votado = localizaCandidato(candidatos, candidato_tmp, cargos[i]);
                        pUmCandidato.apontaProCandidato = candidato_votado;
                        flag_computou = 0;
                        for(j=0;j<qtdCandidatos;j++) {
                            if(strcmp(pUmCandidato.apontaProCandidato->nome, votos[j].apontaProCandidato->nome) || pUmCandidato.apontaProCandidato->numero == votos[j].apontaProCandidato->numero){
                                votos[j].totalDeVotos++;
                                flag_computou=1;
                            }
                        }
                        if(!flag_computou){
                    
                            votos[idx_votos].apontaProCandidato = candidato_votado;
                            votos[idx_votos].totalDeVotos++;
                            idx_votos++;
                        }
                    }else{
                        printf("\n\t\t*Voto não foi contado para %s, pois o candidato não existe*\t\t\n", cargos[i]);
                    }
                    
                     
                }
            }else{
                printf("\n\t\t*Eleitor Inexistente*\t\t\n");
            }
        }

    }while(strcmp(cpf, "-1")!=0);

    apresentaResultado(votos, qtdCandidatos);

    return 0;
}

listaCandidatos carregarCandidatos(char *nomeArq){
    listaCandidatos ans; //retorno da função
    for(int i=0;i<5;i++) ans.qtdCandidatos[i]=0;

    FILE *file = fopen(nomeArq, "r");
    if(file == NULL){
        printf("*Ocorreu algum problema na abertura do arquivo*\n");
        exit(1);
    }
    char leitura[110];
    char *split;
    Candidato candidato_lido;
    int idx=0;
    char subconjunto[3][110];
    while(!feof(file)){
        fscanf(file, " %[^\n]", leitura);//ler a linha toda
        
        split = strtok(leitura, ",");//tokeniza a string 
        while(split!=NULL){
            strcpy(subconjunto[idx++], split);
            split = strtok(NULL, ",");//tokeniza a string 
        }
        // for(int i=0;i<3;i++){
        //     printf("%s\n", subconjunto[i]);
        // }
        strcpy(candidato_lido.nome, subconjunto[1]);
        candidato_lido.numero = atoi(subconjunto[2]);
        Candidato *tmp;
        if(strcmp(subconjunto[0], "presidente")==0){
            //intf("enter");
            ans.presidente = NULL;
            tmp = ans.presidente;
            ans.presidente = (Candidato *) realloc(ans.presidente, (ans.qtdCandidatos[4]+1)*sizeof(Candidato));
            if(ans.presidente == NULL){
                printf("*Ocorreu algum problema na alocação do presidente*\n");
                free(tmp);
                exit(1);
            }
            ans.presidente[ans.qtdCandidatos[4]] = candidato_lido;
            //printf("*%s\n",ans.presidente[ans.qtdCandidatos[4]].nome);
            ans.qtdCandidatos[4]++;

        }else if(strcmp(subconjunto[0], "governador")==0){
            ans.governador = NULL;
            tmp = ans.governador;
            ans.governador = (Candidato *) realloc(ans.governador, (ans.qtdCandidatos[3]+1)*sizeof(Candidato));
            if(ans.governador == NULL){
                printf("*Ocorreu algum problema na alocação do governador*\n");
                free(tmp);
                exit(1);
            }
            ans.governador[ans.qtdCandidatos[3]] = candidato_lido;
            ans.qtdCandidatos[3]++;
        }else if(strcmp(subconjunto[0], "senador")==0){
            ans.senador = NULL;
            tmp = ans.senador;
            ans.senador = (Candidato *) realloc(ans.senador, (ans.qtdCandidatos[2]+1)*sizeof(Candidato));
            if(ans.senador == NULL){
                printf("*Ocorreu algum problema na alocação do senador*\n");
                free(tmp);
                exit(1);
            }
            ans.senador[ans.qtdCandidatos[2]] = candidato_lido;
            ans.qtdCandidatos[2]++;
        }else if(strcmp(subconjunto[0], "deputada estadual")==0){
            ans.dep_estadual = NULL;
            tmp = ans.dep_estadual;
            ans.dep_estadual = (Candidato *) realloc(ans.dep_estadual, (ans.qtdCandidatos[0]+1)*sizeof(Candidato));
            if(ans.dep_estadual == NULL){
                printf("*Ocorreu algum problema na alocação do deputada estadual*\n");
                free(tmp);
                exit(1);
            }
            ans.dep_estadual[ans.qtdCandidatos[0]] = candidato_lido;
            ans.qtdCandidatos[0]++;
        }else if(strcmp(subconjunto[0], "deputada federal")==0){
            ans.dep_federal = NULL;
            tmp = ans.dep_federal;
            ans.dep_federal = (Candidato *) realloc(ans.dep_federal, (ans.qtdCandidatos[1]+1)*sizeof(Candidato));
            if(ans.dep_federal == NULL){
                printf("*Ocorreu algum problema na alocação do deputada federal*\n");
                free(tmp);
                exit(1);
            }
            ans.dep_federal[ans.qtdCandidatos[1]] = candidato_lido;
            ans.qtdCandidatos[1]++;
        }

        idx=0;
        //printf("\n");
    }
    fclose(file);

    return ans;
}

Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores){
    Eleitor *ans = NULL; 
    Eleitor *tmp;
    FILE *file = fopen(nomeArq, "r");
    if(file == NULL){
        printf("*Ocorreu algum problema na abertura do arquivo*\n");
        exit(1);
    }

    char leitura[110];
    int ehONome=0;
    char *split;
    while(!feof(file)){
        tmp = ans;
        ans = (Eleitor *)realloc(ans, (*qtdEleitores+1)*sizeof(Eleitor));
        
        if(ans == NULL){
            printf("*Ocorreu algum problema na alocação do eleitor*\n");
            free(tmp);
            exit(1);
        }
        fscanf(file, " %[^\n]", leitura);
        split = strtok(leitura, ",");//tokeniza a string 
        while(split!=NULL){
            if(ehONome&1){
                strcpy(ans[(*qtdEleitores)].nome, split);
            }else{
                strcpy(ans[(*qtdEleitores)].cpf, split);
            }
            ehONome = !ehONome;
            split = strtok(NULL, ",");//tokeniza a string 
        }
        (*qtdEleitores)++;
    }
    fclose(file);
    return ans;
}

int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt){
    int i, j;
    for(i=0;i<5;i++){
        for(int j=0;j<listaC.qtdCandidatos[i];j++){
            if(i==0){
                if(listaC.dep_estadual[i].numero == candidatoAt.numero){
                    return 1;
                }
            }else if(i==1){
                if((listaC.dep_federal[i].numero == candidatoAt.numero)){
                    return 1;
                }
            }else if(i==2){
                if((listaC.senador[i].numero == candidatoAt.numero)){
                    return 1;
                }
            }else if(i==3){
                if((listaC.governador[i].numero == candidatoAt.numero)){
                    return 1;
                }
            }else if(i==4){
                if((listaC.presidente[i].numero == candidatoAt.numero)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt, int qtdEleitores){
    for(int i=0;i<qtdEleitores;i++) if(strcpy(listaE[i].nome, eleitorAt.nome)==0 && strcpy(listaE[i].cpf, eleitorAt.cpf)==0) return 1;
    return 0;
}

void apresentaResultado(TotalVoto *votos, int qtdCandidatos){
    for(int i=0;i<qtdCandidatos;i++){
        printf("\nCandidato %s.", votos[i].apontaProCandidato->nome);
        printf("Total de votos.: %d\n\n", votos[i].totalDeVotos);
    }
}

Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo){
    Candidato *ans=NULL;
    if(strcmp(cargo, "presidente")==0){
        for(int i=0;i<listaC.qtdCandidatos[4];i++) if(strcmp(listaC.presidente[i].nome, candidatoAt.nome)==0 || listaC.presidente[i].numero == candidatoAt.numero){
            ans = &(listaC.presidente[i]);
        }

    }else if(strcmp(cargo, "governador")==0){
        for(int i=0;i<listaC.qtdCandidatos[3];i++) if(strcmp(listaC.governador[i].nome, candidatoAt.nome)==0 || listaC.governador[i].numero == candidatoAt.numero){
            ans = &(listaC.governador[i]);
        }
    }else if(strcmp(cargo, "senador")==0){
        for(int i=0;i<listaC.qtdCandidatos[2];i++) if(strcmp(listaC.senador[i].nome, candidatoAt.nome)==0 || listaC.senador[i].numero == candidatoAt.numero){
            ans = &(listaC.senador[i]);
        }
        
    }else if(strcmp(cargo, "deputada estadual")==0){
        for(int i=0;i<listaC.qtdCandidatos[0];i++) if(strcmp(listaC.dep_estadual[i].nome, candidatoAt.nome)==0 || listaC.dep_estadual[i].numero == candidatoAt.numero){
            ans = &(listaC.dep_estadual[i]);
        }
    }else if(strcmp(cargo, "deputada federal")==0){
        for(int i=0;i<listaC.qtdCandidatos[1];i++) if(strcmp(listaC.dep_federal[i].nome, candidatoAt.nome)==0 || listaC.dep_federal[i].numero == candidatoAt.numero){
            ans = &(listaC.dep_federal[i]);
        }
    }

    return ans;
}
