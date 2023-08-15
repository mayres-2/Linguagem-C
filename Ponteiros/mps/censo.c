#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    char nome[50];
    char raca[50];
    int idade;
    float salario;
    char CPF[12];
} Pessoa;

typedef struct {
    char nome[50];
    int codigo; //codigo unico que identifica cada cidade
    Pessoa * cidadaos;
    int capacidade;
    //eu coloquei isso
    int n_cidadaos;
} Cidade;


Cidade * NovaCidade(Cidade *censo, int *tam);
void InserirOuAtualizar(Cidade *censo, int tam);
void Remover(Cidade *censo, int tam);
void Procura(Cidade *censo, int tam);
void ViewTable(Cidade *censo, int tam);
void Desloca(Cidade *censo, int tam);

/*----------------------------------------------------------------------*/
int main(){
    Cidade *censo = NULL;
    int qtd_cidades=0;
    int escolha = -1;

    do {
        printf("======MENU======\n");
        printf(" 1..Cadastrar Cidade\n");
        printf(" 2..Procurar as informacoes de um CPF\n");
        printf(" 3..Ver todos os dados registrados\n");
        printf(" 4..Adcionar/Atualizar os dados de uma pessoa\n");
        printf(" 5..Remover uma pessoa\n");
        printf(" 6..Sair\n");

        scanf("%d", &escolha);

        if(escolha == 1){
            censo = NovaCidade(censo, &qtd_cidades);
        }
        else if(escolha == 2){
            Procura(censo, qtd_cidades);
        }
        else if(escolha == 3){
            ViewTable(censo, qtd_cidades);
        }
        else if(escolha == 4){
            InserirOuAtualizar(censo, qtd_cidades);
        }
        else if(escolha == 5){
            Remover(censo, qtd_cidades);
        }
        else if(escolha == 6){
            printf("Saindo..\n");
        }
    } while (escolha != 6);
    
    Desloca(censo, qtd_cidades);
    free(censo);
    return 0;
}
/*----------------------------------------------------------------------*/



//ok//cria cidade//
Cidade * NovaCidade(Cidade *censo, int *tam){
    int otEscolha = -1;
    Cidade *tmp = (Cidade *) realloc (censo, (*tam + 1) * sizeof(Cidade));
    if(tmp == NULL){
        printf("Erro de Alocacao\n");
        Desloca(censo, *tam);
        free(tmp);
        exit(1);
    }
    else{
        censo = tmp;
        (*tam)++;
    }
    int indexCidade = *tam;

    //provavelmente nao vai entrar aqui, mas esta ai
    if(*tam==0){
        Cidade nova[1];
        printf("Nome dessa nova cidade?\n"); scanf(" %s", nova[0].nome);
        printf("Codigo dessa cidade?\n"); scanf("%d", &nova[0].codigo);
        printf("Capacidade de pessoa dessa cidade?\n"); scanf("%d", &nova[0].capacidade);
        printf("Tem alguem morando nessa cidade?\n(1)sim\n(2)nao\n"); scanf("%d", &otEscolha);
        censo[0] = nova[0];
        if(otEscolha==1){
            printf("Quantas pessoas moram nessa cidade?\n"); scanf("%d", &tmp[0].n_cidadaos);
            if(censo[indexCidade].capacidade >= tmp[0].n_cidadaos){
                censo[indexCidade].n_cidadaos = tmp[0].n_cidadaos;
                //era para de algum jeito adcionar os dados dessa quantidade de pessoas no censo;
                InserirOuAtualizar(censo, *tam);
            }
            else {
                printf("nao tem lugar nessa cidade para mais pessoas\n");
                return censo;
            } 
        }
        else if(otEscolha==2){
            censo[0].n_cidadaos = 0;
            printf("Ok...\n");
        }
    }

    else {
        //deveria estar recebendo algo do ultimo valor *tam
        Cidade nova[1];
        printf("Nome dessa cidade?\n"); scanf(" %s", nova[0].nome);
        printf("Codigo dessa cidade?\n"); scanf("%d", &nova[0].codigo);
        printf("Capacidade de pessoa dessa cidade?\n"); scanf("%d", &nova[0].capacidade);
        printf("Tem alguem morando nessa cidade?\n(1)sim\n(2)nao\n"); scanf("%d", &otEscolha);
        censo[indexCidade] = nova[0];
        if(otEscolha==1){
            printf("Quantas pessoas moram nessa cidade?\n"); scanf("%d", &tmp[0].n_cidadaos);
            if(censo[indexCidade].capacidade >= tmp[0].n_cidadaos){
                censo[indexCidade].n_cidadaos = tmp[0].n_cidadaos;
                //era para de algum jeito adcionar os dados dessa quantidade de pessoas no censo;
                InserirOuAtualizar(censo, *tam);
            } 
            else{
                printf("nao tem lugar nessa cidade para mais pessoas\n");
                return censo;
            }
        }
        else if(otEscolha==2){  //////
            censo[indexCidade].n_cidadaos = 0;
            printf("Ok...\n");
        }
        
    }

    printf("Cidade cadastrada\n");
    free(tmp);
    return censo;
}

//insere ou atualiza uma pessoa
void InserirOuAtualizar(Cidade *censo, int tam){
    Pessoa new;
    int otEscolha = -1;
    char nome[50];
    bool encontrado=false;

    printf("Voce deseja \n(1) inserir os dados de uma pessoa ou \n(2) atualizar os dados de uma pessoa? \n");
    scanf("%d", &otEscolha);
    printf("Qual a cidade desse cidadao?\n"); scanf(" %s", nome);

    if (censo==NULL) {
        printf("cidade nao encontrada\n");
        return;
    }
    //so tem uma cidade
    else if(tam==0 && (strcmp(censo[0].nome, nome) == 0)){
        //uma pessoa
        if(censo[0].n_cidadaos == 0){
            //inserir
            if(otEscolha==1){
                Pessoa *newof = (Pessoa *) realloc(censo[0].cidadaos, (censo[0].n_cidadaos+1) * sizeof(Pessoa));
                if(newof == NULL){
                    printf("Erro de alocacao\n");
                    Desloca(censo, tam);
                    free(newof);
                    exit(1);
                }
                else {
                    censo[0].cidadaos = newof;
                    censo[0].n_cidadaos++;
                }
                if(censo[0].capacidade >= censo[0].n_cidadaos){
                    printf("Qual o CPF desse cidadao?\n"); scanf(" %s", newof[0].CPF);

                    if(strcmp(newof[0].CPF, censo[0].cidadaos[censo[0].n_cidadaos].CPF) == 0){
                        printf("jah existe uma pessoa com esse cpf nessa cidade\n");
                        return;
                    }
                    
                    else{
                        strcpy(censo[0].cidadaos[censo[0].n_cidadaos].CPF, newof[0].CPF);
                        printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[censo[0].n_cidadaos].nome);
                        printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[censo[0].n_cidadaos].idade);
                        printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[censo[0].n_cidadaos].raca);
                        printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[censo[0].n_cidadaos].salario);
                        return;
                    }
                }
                else {
                    printf("nao tem lugar nessa cidade para mais pessoas\n");
                    censo[0].n_cidadaos--;
                    return;
                }
            }

            //atualizar
            else {
                printf("Qual o CPF desse cidadao?\n"); scanf(" %s", new.CPF);
                for(int k=1; k<=censo[0].n_cidadaos; k++){
                    if(strcmp(new.CPF, censo[0].cidadaos[k].CPF) == 0){
                        encontrado = true;
                        printf("O que voce deseja atuzalizar nesse cidadao? \n(1)tudo\n(2)idade\n(3)raca\n(4)salario\n(5)nome\n"); 
                        scanf("%d", &otEscolha);
                        if(otEscolha==1){
                            printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].nome);
                            printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[k].idade);
                            printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].raca);
                            printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[k].salario);
                        }
                        else if(otEscolha==2){
                            printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[k].idade);
                        }
                        else if(otEscolha==3){
                            printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].raca);
                        }
                        else if(otEscolha==4){
                            printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[k].salario);
                        }
                        else if(otEscolha==5){
                            printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].nome);
                        }
                        else{
                            printf("Opcao invalida\n");
                        }
                        return;
                    }
                }

                if(encontrado==false){
                    printf("pessoa nao encontrada\n");
                    return;
                }
            }
        }

        //tem mais de uma pessoa
        else if(censo[0].n_cidadaos>0){
            
            //inserir
            if(otEscolha==1){
                Pessoa *newof = censo[0].cidadaos;
                censo[0].cidadaos = (Pessoa *) realloc (censo[0].cidadaos, (censo[0].n_cidadaos+1) * sizeof(Pessoa));
                if(censo[0].cidadaos == NULL){
                    printf("Erro de alocacao\n");
                    Desloca(censo, tam);
                    free(newof);
                    exit(1);
                }
                censo[0].n_cidadaos++;
                if(censo[0].capacidade >= censo[0].n_cidadaos){
                    printf("Qual o CPF desse cidadao?\n"); scanf(" %s", newof[0].CPF);
                    if(strcmp(newof[0].CPF, censo[0].cidadaos[censo[0].n_cidadaos].CPF) == 0){
                        printf("jah existe uma pessoa com esse cpf nessa cidade\n");
                        return;
                    }
                    else{
                        strcpy(censo[0].cidadaos[censo[0].n_cidadaos].CPF, newof[0].CPF);
                        printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[censo[0].n_cidadaos].nome);
                        printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[censo[0].n_cidadaos].idade);
                        printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[censo[0].n_cidadaos].raca);
                        printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[censo[0].n_cidadaos].salario);
                        return;
                    }
                }
                else {
                    printf("nao tem lugar nessa cidade para mais pessoas\n");
                    censo[0].n_cidadaos--;
                    return;
                }
            }

            //atualizar
            else {
                printf("Qual o CPF desse cidadao?\n"); scanf(" %s", new.CPF);
                for(int k=1; k<=censo[0].n_cidadaos; k++){
                    if(strcmp(new.CPF, censo[0].cidadaos[k].CPF) == 0){
                        encontrado = true;
                        printf("O que voce deseja atuzalizar nesse cidadao? \n(1)tudo\n(2)idade\n(3)raca\n(4)salario\n(5)nome\n"); 
                        scanf("%d", &otEscolha);
                        if(otEscolha==1){
                            printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].nome);
                            printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[k].idade);
                            printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].raca);
                            printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[k].salario);
                        }
                        else if(otEscolha==2){
                            printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[0].cidadaos[k].idade);
                        }
                        else if(otEscolha==3){
                            printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].raca);
                        }
                        else if(otEscolha==4){
                            printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[0].cidadaos[k].salario);
                        }
                        else if(otEscolha==5){
                            printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[0].cidadaos[k].nome);
                        }
                        else{
                            printf("Opcao invalida\n");
                        }
                        return;
                    }
                }

                if(encontrado==false){
                    printf("pessoa nao encontrada\n");
                    return;
                }
            }
        }
    }

    //mais de uma cidade
    else if (tam>0) {
        for(int j=0; j<tam; j++){
            if(strcmp(censo[j].nome, nome) == 0){
                //inserir
                if(otEscolha==1){
                    Pessoa *newof = censo[j].cidadaos;
                    censo[j].cidadaos = (Pessoa *) realloc (censo[j].cidadaos, (censo[j].n_cidadaos+1) * sizeof(Pessoa));
                    if(censo[j].cidadaos == NULL){
                        printf("Erro de alocacao\n");
                        Desloca(censo, tam);
                        free(newof);
                        exit(1);
                    }
                    censo[j].n_cidadaos++;
                    if(censo[j].capacidade>=censo[0].n_cidadaos){
                        printf("Qual o CPF desse cidadao?\n"); scanf(" %s", newof[0].CPF);

                        if(strcmp(newof[0].CPF, censo[0].cidadaos[censo[0].n_cidadaos].CPF) == 0){
                            printf("jah existe uma pessoa com esse cpf nessa cidade\n");
                            return;
                        }

                        else{
                            strcpy(censo[j].cidadaos[censo[0].n_cidadaos].CPF, newof[0].CPF);
                            printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[censo[j].n_cidadaos].nome);
                            printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[j].cidadaos[censo[j].n_cidadaos].idade);
                            printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[censo[j].n_cidadaos].raca);
                            printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[j].cidadaos[censo[j].n_cidadaos].salario);
                            return;
                        }
                    }
                    else {
                        printf("nao tem lugar nessa cidade para mais pessoas\n");
                        censo[j].n_cidadaos--;
                        return;
                    }
                }

                //atualizar
                else{
                    printf("Qual o CPF desse cidadao?\n"); scanf(" %s", new.CPF);
                    for(int k=0; k<censo[j].n_cidadaos; k++){
                        if(strcmp(new.CPF, censo[0].cidadaos[k].CPF) == 0){
                            encontrado = true;
                            printf("O que voce deseja atuzalizar nesse cidadao? \n(1)tudo\n(2)idade\n(3)raca\n(4)salario\n(5)nome\n"); 
                            scanf("%d", &otEscolha);
                            if(otEscolha==1){
                                printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[k].nome);
                                printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[j].cidadaos[k].idade);
                                printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[k].raca);
                                printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[j].cidadaos[k].salario);
                                return;
                            }
                            else if(otEscolha==2){
                                printf("Qual a idade desse cidadao?\n"); scanf("%d", &censo[j].cidadaos[k].idade);
                            }
                            else if(otEscolha==3){
                                printf("Qual a etinia desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[k].raca);
                            }
                            else if(otEscolha==4){
                                printf("Qual o salario desse cidadao?\n"); scanf("%f", &censo[j].cidadaos[k].salario);
                            }
                            else if(otEscolha==5){
                                printf("Qual o nome desse cidadao?\n"); scanf(" %s", censo[j].cidadaos[k].nome);
                            }
                            else{
                                printf("Opcao invalida");
                            }  
                            return;
                        }
                    }

                    if(encontrado==false){
                        printf("pessoa nao encontrada\n");
                        return;
                    }
                }
            }
        }
    }

    else{
        printf("cidade nao encontrada\n");
        return;
    }


}

//remove uma pessoa
void Remover(Cidade *censo, int tam){
    Pessoa removerP;
    bool encontrada = false;

    printf("CPF da pessoa? "); scanf(" %s", removerP.CPF);

    for(int i=0; i<tam; i++){
        for(int j=0; j<censo[i].n_cidadaos; j++){
            if(strcmp(removerP.CPF, censo[i].cidadaos[j].CPF)==0){
                encontrada = true;
                censo[i].cidadaos[j] = censo[i].cidadaos[censo[i].n_cidadaos];
                censo[i].cidadaos = (Pessoa *) realloc (censo[i].cidadaos, (censo[i].n_cidadaos - 1) * sizeof(Pessoa));
                censo[i].n_cidadaos--;
                printf("Pessoa Removida\n");
                return;
            }
        }
    }

    if(encontrada == false){
        printf("pessoa nao encontrada\n");
        return;
    }

}

//procura uma pessoa
void Procura(Cidade *censo, int tam){
    Pessoa procurada;


    bool encontrado=false;
    printf("Qual o CPF desse cidadao?\n"); scanf(" %s", procurada.CPF);

    //se tam==0
    if(tam==0){
        for(int k=1; k<=censo[0].n_cidadaos; k++){
            if(strcmp(procurada.CPF, censo[0].cidadaos[k].CPF) == 0){
                encontrado = true;
                printf("nome desse cidadao: %s\n", censo[0].cidadaos[k].nome);
                printf("idade desse cidadao: %d\n", censo[0].cidadaos[k].idade);
                printf("etinia desse cidadao: %s\n", censo[0].cidadaos[k].raca);
                printf("salario desse cidadao: %.2f\n", censo[0].cidadaos[k].salario);
                return;
            }
        }
    }
    //se tam>0
    else if(tam>0){
        for(int j=0; j<tam; j++){
            for(int k=1; k<=censo[j].n_cidadaos; k++){
                if(strcmp(procurada.CPF, censo[0].cidadaos[k].CPF) == 0){
                    encontrado = true;
                    printf("nome desse cidadao: %s\n", censo[j].cidadaos[k].nome);
                    printf("idade desse cidadao: %d\n", censo[j].cidadaos[k].idade);
                    printf("etinia desse cidadao: %s\n", censo[j].cidadaos[k].raca);
                    printf("salario desse cidadao: %.2f\n", censo[j].cidadaos[k].salario);
                    return;
                }
            }
        }
    }

    if(encontrado==false){
        printf("pessoa nao encontrada\n");
        return;
    }
}

//ve tudo
void ViewTable(Cidade *censo, int tam){ 
    if(censo==NULL){
        printf("nao tem cidades cadastradas no censo\n");
        return;
    }
    //se tam==0
    else if(tam==0){
        printf("Nome da cidade: %s\n", censo[0].nome);
        printf("Codigo da cidade: %d\n", censo[0].codigo);
        printf("Capacidade de pessoa para morar: %d\n", censo[0].capacidade);
        printf("%d pessoas que moram na cidade\n", censo[0].n_cidadaos);
        for(int k=1; k<=censo[0].n_cidadaos; k++){
            printf("nome desse cidadao: %s\n", censo[0].cidadaos[k].nome);
            printf("idade desse cidadao: %d\n", censo[0].cidadaos[k].idade);
            printf("etinia desse cidadao: %s\n", censo[0].cidadaos[k].raca);
            printf("salario desse cidadao: %.2f\n", censo[0].cidadaos[k].salario);  
        }
        return;
    }
    //se tam>0
    else if(tam>0){
        for(int j=0; j<tam; j++){
            printf("Nome da cidade: %s\n", censo[j].nome);
            printf("Codigo da cidade: %d\n", censo[j].codigo);
            printf("Capacidade de pessoa para morar: %d\n", censo[j].capacidade);
            printf("%d pessoas que moram na cidade\n", censo[j].n_cidadaos);
            for(int k=1; k<=censo[j].n_cidadaos; k++){
                printf("nome desse cidadao: %s\n", censo[j].cidadaos[k].nome);
                printf("idade desse cidadao: %d\n", censo[j].cidadaos[k].idade);
                printf("etinia desse cidadao: %s\n", censo[j].cidadaos[k].raca);
                printf("salario desse cidadao: %.2f\n", censo[j].cidadaos[k].salario);
                
            }
        }
        return;
    }
}

//da free em todos os ponteiros dentro do censo
void Desloca(Cidade *censo, int tam){
    if(tam==0){
        free(censo[0].cidadaos);
        free(censo);
    }
    else if(tam>=0){
        for(int i=0; i<tam; i++){
            free(censo[i].cidadaos);
        }
        free(censo);
    }
    else{
        free(censo);
    }
}