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
void InserirOuAtualizar(Cidade **censo, int tam);
void Remover(Cidade *censo, int tam);
void Procura(Cidade *censo, int tam);
void ViewTable(Cidade *censo, int tam);
void Desloca(Cidade *censo, int tam);


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
            InserirOuAtualizar(&censo, qtd_cidades);
        }
        else if(escolha == 5){
            Remover(censo, qtd_cidades);
        }
        else if(escolha == 6){
            printf("Saindo..\n");
        }
    } while (escolha != 6);
    
    Desloca(censo, qtd_cidades);
    return 0;
}




//ok//cria cidade//
Cidade * NovaCidade(Cidade *censo, int *tam){
    int otEscolha = -1;
    int indexCidade = *tam;
    Cidade *tmp = censo;
    censo = (Cidade *) realloc (censo, (*tam + 1) * sizeof(Cidade));
    if(censo == NULL){
        printf("Erro de Alocacao\n");
        Desloca(censo, *tam);
        free(tmp);
        exit(1);
    }
    else{
        censo[(*tam)].cidadaos = NULL;    
        (*tam)++;
    }

    
    if(indexCidade==0){
        printf("Nome dessa nova cidade?\n"); scanf(" %s", censo[indexCidade].nome);
        printf("Codigo dessa cidade?\n"); scanf("%d", &censo[indexCidade].codigo);
        printf("Capacidade de pessoas dessa cidade?\n"); scanf("%d", &censo[indexCidade].capacidade);
        printf("Tem alguem morando nessa cidade?\n(1)sim\n(2)nao\n"); scanf("%d", &otEscolha);
        if(otEscolha==1){
            printf("Quantas pessoas moram nessa cidade?\n"); scanf("%d", &tmp[0].n_cidadaos);
            if(censo[indexCidade].capacidade >= tmp[0].n_cidadaos){
                censo[indexCidade].n_cidadaos = tmp[0].n_cidadaos;
                //era para de algum jeito adcionar os dados dessa quantidade de pessoas no censo;
                InserirOuAtualizar(&censo, *tam);
            }
            else {
                printf("nao tem lugar nessa cidade para mais pessoas\n");
                return censo;
            }
        }
        else if(otEscolha==2){
            censo[indexCidade].n_cidadaos = 0;
            printf("Ok...\n");
        }
    }

    else {
        //deveria estar recebendo algo do ultimo valor *tam
        printf("Nome dessa cidade?\n"); scanf(" %s", censo[indexCidade].nome);
        printf("Codigo dessa cidade?\n"); scanf("%d", &censo[indexCidade].codigo);
        for(int i=0; i<*tam-1; i++){
            if(censo[i].codigo == censo[indexCidade].codigo){
                printf("Esse codigo jah esta cadastrado em outra cidade\n");
                
                tmp = censo;
                censo = (Cidade *) realloc (censo, (*tam -1) *sizeof(Cidade));
                if(censo==NULL){printf("Erro\n"); free(tmp); exit(1);}
                
                (*tam)--;
                return censo; 
            }
        }
        printf("Capacidade de pessoa dessa cidade?\n"); scanf("%d", &censo[indexCidade].capacidade);
        printf("Tem alguem morando nessa cidade?\n(1)sim\n(2)nao\n"); scanf("%d", &otEscolha);
        if(otEscolha==1){
            printf("Quantas pessoas moram nessa cidade?\n"); scanf("%d", &tmp[0].n_cidadaos);
            if(censo[indexCidade].capacidade >= tmp[0].n_cidadaos){
                censo[indexCidade].n_cidadaos = tmp[0].n_cidadaos;
                //era para de algum jeito adcionar os dados dessa quantidade de pessoas no censo;
                InserirOuAtualizar(&censo, *tam);
            } 
            else{
                printf("nao tem lugar nessa cidade para mais pessoas\n");
                return censo;
            }
        }
        else if(otEscolha==2){
            censo[indexCidade].n_cidadaos = 0;
            printf("Ok...\n");
        }
        
    }

    printf("Cidade cadastrada\n");
    return censo;
}

//nao//ta//ok//insere ou atualiza uma pessoa//
void InserirOuAtualizar(Cidade **censo, int tam){
    Pessoa new;
    int otEscolha = -1;
    int codigo=0, indexCidade=0;
    bool encontrado=false;

    printf("Voce deseja \n(1) inserir os dados de uma pessoa ou \n(2) atualizar os dados de uma pessoa? \n");
    scanf("%d", &otEscolha);
    printf("Qual o codigo da cidade desse cidadao?\n"); scanf("%d", &codigo);
    

    if (censo==NULL) {
        printf("cidade nao encontrada\n");
        return;
    }
    
    else if(tam>0){
        for(int i=0; i<tam && encontrado==false; i++){
            if((*censo)[i].codigo == codigo){
                encontrado = true;
                indexCidade=i;
            }
        }
        
        //
        if(!encontrado){
            printf("cidade nao encontrada\n");
            return;
        }
        
        
        int indexPessoa = (*censo)[indexCidade].n_cidadaos;
        //inserir
        if(otEscolha==1){
            Pessoa novaPessoa;
            Pessoa *newof = (*censo)[indexCidade].cidadaos;
            (*censo)[indexCidade].cidadaos = (Pessoa *) realloc((*censo)[indexCidade].cidadaos, ((*censo)[indexCidade].n_cidadaos+1) * sizeof(Pessoa));
            
            if((*censo) == NULL){
                printf("Erro de alocacao\n");
                free(newof);
                exit(1);
            }
            else {
                (*censo)[indexCidade].n_cidadaos++;
            }

            if((*censo)[indexCidade].capacidade >= (*censo)[indexCidade].n_cidadaos){
                printf("Qual o CPF desse cidadao?\n"); scanf(" %s", novaPessoa.CPF);
                    
                if(strcmp(novaPessoa.CPF, (*censo)[indexCidade].cidadaos[indexPessoa].CPF) == 0){
                    printf("jah existe uma pessoa com esse cpf nessa cidade\n");
                    return;
                }
                else{
                    strcpy((*censo)[indexCidade].cidadaos[indexPessoa].CPF, novaPessoa.CPF);
                    printf("Qual o nome desse cidadao?\n"); 
                        getchar();
                        fgets((*censo)[indexCidade].cidadaos[indexPessoa].nome, 50, stdin);
                        int i=0; 
                        while ((*censo)[indexCidade].cidadaos[indexPessoa].nome[i] != '\n'){
                            i++;
                        } 
                        (*censo)[indexCidade].cidadaos[indexPessoa].nome[i++] = '\0';
                    printf("Qual a idade desse cidadao?\n"); scanf("%d", &(*censo)[indexCidade].cidadaos[indexPessoa].idade);
                    printf("Qual a etinia desse cidadao?\n"); 
                        getchar();
                        fgets((*censo)[indexCidade].cidadaos[indexPessoa].raca, 50, stdin);
                        i=0; 
                        while ((*censo)[indexCidade].cidadaos[indexPessoa].raca[i] != '\n'){
                            i++;
                        } 
                        (*censo)[indexCidade].cidadaos[indexPessoa].raca[i++] = '\0';
                    printf("Qual o salario desse cidadao?\n"); scanf("%f", &(*censo)[indexCidade].cidadaos[indexPessoa].salario);
                    return;
                }
            }
            else {
                printf("nao tem lugar nessa cidade para mais pessoas\n");
                (*censo)[indexCidade].n_cidadaos--;
                return;
            }
        }

        //atualizar
        else {
            printf("Qual o CPF desse cidadao?\n"); scanf(" %s", new.CPF);
            for(int k=0; k<(*censo)[indexCidade].n_cidadaos+1; k++){
                if(strcmp(new.CPF, (*censo)[indexCidade].cidadaos[k].CPF) == 0){
                    encontrado = true;
                    printf("O que voce deseja atuzalizar nesse cidadao? \n(1)tudo\n(2)idade\n(3)raca\n(4)salario\n(5)nome\n"); 
                    scanf("%d", &otEscolha);
                    if(otEscolha==1){
                        printf("Qual o nome desse cidadao?\n");
                            getchar();
                            fgets((*censo)[indexCidade].cidadaos[k].nome, 50, stdin);
                            int i=0; 
                            while ((*censo)[indexCidade].cidadaos[k].nome[i] != '\n'){
                                i++;
                            } 
                            (*censo)[indexCidade].cidadaos[k].nome[i++] = '\0';
                        printf("Qual a idade desse cidadao?\n"); scanf("%d", &(*censo)[indexCidade].cidadaos[k].idade);
                        printf("Qual a etinia desse cidadao?\n"); 
                            getchar();
                            fgets((*censo)[indexCidade].cidadaos[k].raca, 50, stdin);
                            i=0; 
                            while ((*censo)[indexCidade].cidadaos[k].raca[i] != '\n'){
                                i++;
                            }
                            (*censo)[indexCidade].cidadaos[k].raca[i++] = '\0';
                        printf("Qual o salario desse cidadao?\n"); scanf("%f", &(*censo)[indexCidade].cidadaos[k].salario);
                    }
                    else if(otEscolha==2){
                        printf("Qual a idade desse cidadao?\n"); scanf("%d", &(*censo)[indexCidade].cidadaos[k].idade);
                    }
                    else if(otEscolha==3){
                        printf("Qual a etinia desse cidadao?\n"); 
                            getchar();
                            fgets((*censo)[indexCidade].cidadaos[k].raca, 50, stdin);
                            int i=0; 
                            while ((*censo)[indexCidade].cidadaos[k].raca[i] != '\n'){
                                i++;
                            } 
                            (*censo)[indexCidade].cidadaos[k].raca[i++] = '\0';
                    }
                    else if(otEscolha==4){
                        printf("Qual o salario desse cidadao?\n"); scanf("%f", &(*censo)[indexCidade].cidadaos[k].salario);
                    }
                    else if(otEscolha==5){
                        printf("Qual o nome desse cidadao?\n");
                            getchar();
                            fgets((*censo)[indexCidade].cidadaos[k].nome, 50, stdin);
                            int i=0; 
                            while ((*censo)[indexCidade].cidadaos[k].nome[i] != '\n'){
                                i++;
                            } 
                            (*censo)[indexCidade].cidadaos[k].nome[i++] = '\0';
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
    
    else{
        printf("cidade nao encontrada\n");
        return;
    }

}

//nao//sei//remove uma pessoa
void Remover(Cidade *censo, int tam){
    Pessoa removerP;
    bool encontrada = false;

    printf("CPF da pessoa? "); scanf(" %s", removerP.CPF);

    for(int i=0; i<tam; i++){
        for(int j=0; j<censo[i].n_cidadaos; j++){
            if(strcmp(removerP.CPF, censo[i].cidadaos[j].CPF)==0){
                encontrada = true;
                censo[i].cidadaos[j] = censo[i].cidadaos[censo[i].n_cidadaos];
                Pessoa *tmp = censo[i].cidadaos;
                censo[i].cidadaos = (Pessoa *) realloc (censo[i].cidadaos, (censo[i].n_cidadaos - 1) * sizeof(Pessoa));
                if(censo[i].cidadaos == NULL){
                    printf("Problema de alocacao\n");
                    free(tmp);
                    exit(1);
                }
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

//nao//sei//procura uma pessoa
void Procura(Cidade *censo, int tam){
    Pessoa procurada;
    
    bool encontrado=false;

    printf("Qual o CPF desse cidadao?\n"); scanf(" %s", procurada.CPF);

    //se inicio
    if(tam==0){
        for(int k=0; k<=censo[0].n_cidadaos; k++){
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

    //se 
    else if(tam>0){
        for(int j=0; j<tam; j++){
            for(int k=0; k<=censo[j].n_cidadaos; k++){
                if(strcmp(procurada.CPF, censo[j].cidadaos[k].CPF) == 0){
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

    if(!encontrado){
        printf("pessoa nao encontrada\n");
        return;
    }
}

//ok//ve tudo//
void ViewTable(Cidade *censo, int tam){ 
    if(censo==NULL){
        printf("nao tem cidades cadastradas no censo\n");
        return;
    }
    
    else if(tam>=0){
        for(int j=0; j<tam; j++){
            printf("Nome da cidade: %s\n", censo[j].nome);
            printf("Codigo da cidade: %d\n", censo[j].codigo);
            printf("Capacidade de pessoa para morar: %d\n", censo[j].capacidade);
            printf("%d pessoas que mora(m) na cidade\n", censo[j].n_cidadaos);
            for(int k=0; k<censo[j].n_cidadaos; k++){
                printf("nome desse cidadao: %s\n", censo[j].cidadaos[k].nome);
                printf("idade desse cidadao: %d\n", censo[j].cidadaos[k].idade);
                printf("etinia desse cidadao: %s\n", censo[j].cidadaos[k].raca);
                printf("salario desse cidadao: %.2f\n", censo[j].cidadaos[k].salario);
                
            }
        }
        return;
    }
}

//?//da free em todos os ponteiros dentro do censo
void Desloca(Cidade *censo, int tam){
    if(tam==0){
        free(censo[0].cidadaos);
        free(censo);
    }
    else if(tam>0){
        for(int i=0; i<tam; i++){
            free(censo[i].cidadaos);
        }
        free(censo);
    }
    else{
        free(censo);
    }
}
