#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    int cpf;
} Eleitor;

typedef struct{
    char nome[50];
    int num;
} Candidato;

typedef struct{
    Candidato *deputadof;
    Candidato *deputadoe;
    Candidato *senador;
    Candidato *governador;
    Candidato *presidente;
    int qtdCandidatos[5];
} listaCandidatos;

listaCandidatos carregarCandidatos(char *nomeArq){
    FILE *arquivo;
    listaCandidatos candidatos;
    candidatos.deputadof = NULL;
    candidatos.deputadoe = NULL;
    candidatos.senador = NULL;
    candidatos.governador = NULL;
    candidatos.presidente = NULL;

    // Inicializa o vetor com zero
    for (int i = 0; i < 5; i++){
        candidatos.qtdCandidatos[i] = 0;
    }

    arquivo = fopen(nomeArq, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return candidatos;
    }

    char linha[100];
    char nome[50], num[10];
    int i = 0; // contador de linhas
    while (fgets(linha, 100, arquivo) != NULL) {
        sscanf(linha, "%[^,],%[^\n]", nome, num);
        Candidato candidato;
        strcpy(candidato.nome, nome);
        candidato.num = atoi(num);

        if (i == 0) {// primeira linha: deputados federais

            candidatos.deputadof = (Candidato *)realloc(candidatos.deputadof, (candidatos.qtdCandidatos[0] + 1) * sizeof(Candidato));
            candidatos.deputadof[candidatos.qtdCandidatos[0]] = candidato;
            candidatos.qtdCandidatos[0]++;
        }
        else if (i == 1) {// segunda linha: deputados estaduais
            candidatos.deputadoe = (Candidato *)realloc(candidatos.deputadoe, (candidatos.qtdCandidatos[1] + 1) * sizeof(Candidato));
            candidatos.deputadoe[candidatos.qtdCandidatos[1]] = candidato;
            candidatos.qtdCandidatos[1]++;
        }
        else if (i == 2) {// terceira linha: senadores
            candidatos.senador = (Candidato *)realloc(candidatos.senador, (candidatos.qtdCandidatos[2] + 1) * sizeof(Candidato));
            candidatos.senador[candidatos.qtdCandidatos[2]] = candidato;
            candidatos.qtdCandidatos[2]++;
        }
        else if (i == 3) {// quarta linha: governadores
            candidatos.governador = (Candidato *)realloc(candidatos.governador, (candidatos.qtdCandidatos[3] + 1) * sizeof(Candidato));
            candidatos.governador[candidatos.qtdCandidatos[3]] = candidato;
            candidatos.qtdCandidatos[3]++;
        }
        else if (i == 4) {// quinta linha: presidente
            candidatos.presidente = (Candidato *)realloc(candidatos.presidente, (candidatos.qtdCandidatos[4] + 1) * sizeof(Candidato));
            candidatos.presidente[candidatos.qtdCandidatos[4]] = candidato;
            candidatos.qtdCandidatos[4]++;
        }
        i++;
    }

    fclose(arquivo);
    return candidatos;
}

Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores) {
    FILE *arquivo;
    Eleitor *eleitores = NULL;
    int count = 0;

    arquivo = fopen(nomeArq, "r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    // Conta quantas linhas tem o arquivo
    char c;
    while ((c = fgetc(arquivo)) != EOF){
        if (c == '\n')
        {
            count++;
        }
    }
    rewind(arquivo);

    // Aloca memória para o vetor de eleitores
    eleitores = (Eleitor *)malloc(count * sizeof(Eleitor));

    if (eleitores == NULL){
        printf("Erro ao alocar memória!\n");
        fclose(arquivo);
        return NULL;
    }

    // Lê os dados do arquivo
    int i = 0;
    while (!feof(arquivo) && i < count){
        fscanf(arquivo, "%[^,],%d\n", eleitores[i].nome, &eleitores[i].cpf);
        i++;
    }

    fclose(arquivo);
    *qtdEleitores = count;

    return eleitores;
}

int main() {
    char nomeArq[] = "eleitores.txt";
    int qtdEleitores = 0;
    Eleitor *eleitores = carregarEleitores(nomeArq, &qtdEleitores);
    carregarCandidatos(nomeArq);

    if (eleitores != NULL) {
        free(eleitores);
    }

    return 0;
}