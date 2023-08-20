#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char cpf[13];
    int qtd_notas;
    float *notas;
    float media;
} Aluno;

Aluno *carregaAlunos(int *qtdAlunos);
float *leNotas(int *qtdNotas);
float media(float *notas, int qtdNotas);
void ordena(Aluno *pestes, int qtdAlunos);
void salvaAlunos(Aluno *alunos, int qtddAlunos);


int main(){
    int qtdAlunos=1;
    Aluno *pestes = carregaAlunos(&qtdAlunos);


    for(int i=0; i<qtdAlunos; i++){
        printf("Dados do Alunos: %s\n", pestes[i].nome);
        pestes[i].qtd_notas = 0;
        pestes[i].notas = leNotas(&pestes[i].qtd_notas);
        pestes[i].media = media(pestes[i].notas, pestes[i].qtd_notas);
    }

    ordena(pestes, qtdAlunos); 


    for(int i=0; i<qtdAlunos; i++){
        free(pestes[i].notas);
    }
    free(pestes);

    return 0;
}


Aluno *carregaAlunos(int *qtdAlunos){
    FILE *file = fopen("alunos.txt", "r");
    if(file==NULL){
        printf("Problemas em abrir o arquivo.\n");
        exit(1);
    }

    /*int i=0;
    char qts;
    seek(file, SEEK_SET);
    while(!feof(file)){
        fscanf(file, "%c", qts);
        if(qts == '\n'){
            i++;
        }
    }
    (*qtdAlunos) = qts;*/

    Aluno *alunos = (Aluno *) malloc ((*qtdAlunos) * sizeof(Aluno));
    if(alunos==NULL){
        printf("Problema de alocacao de memoria\n");
        exit(1);
    }

    for(int i=0; i<(*qtdAlunos); i++){
        fscanf(file, " %99[^','],", alunos[i].nome);
        alunos[i].nome[strlen(alunos[i].nome) + 1] = '\0';
        fscanf(file, " %12[^\n]", alunos[i].cpf);
        alunos[i].cpf[strlen(alunos[i].cpf) + 1] = '\0';
    }

    fclose(file);
    return alunos;
}   

//ok//
float *leNotas(int *qtdNotas){
    float *notas=NULL;
    float nota=0;
    
    int i=0;
    while(nota >= 0){
        notas = (float *) realloc(notas, (i+1) * sizeof(float));
        if(notas==NULL){
            printf("Problema de alocar\n");
            exit(1);
        }

        printf("Digite a nota: \n");
        scanf("%f", &nota);

        notas[i] = nota;
        i++;
    }

    (*qtdNotas) = i;

    notas = (float *) realloc(notas, (*qtdNotas) * sizeof(float));

    return notas;
}

//ok//
float media(float *notas, int qtdNotas){
    float media;
    float soma=0;

    for(int i=0; i<qtdNotas; i++){
        soma = soma + notas[i];
    }

    media = soma/qtdNotas;

    return media;
}

//testar//
void ordena(Aluno *alunos, int qtdAlunos){
    Aluno tmp;

    //bublle sort
    for(int i=0; i<qtdAlunos; i++){
        for(int j=0; j<qtdAlunos - i - 1; j++){
            if(alunos[j].media > alunos[j+1].media){
                tmp = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = tmp;
            }
        }
    }
    
    salvaAlunos(alunos, qtdAlunos);

}

//testar//
void salvaAlunos(Aluno *alunos, int qtdAlunos){
    FILE *file = fopen("alunos.bin", "wb");
    if(file==NULL){
        printf("Problema em abrir o arquivo\n");
        exit(1);
    }

    fwrite(&qtdAlunos, sizeof(int), 1, file);
    for(int i = 0; i<qtdAlunos; i++){
        fwrite(alunos[i].nome, sizeof(char), strlen(alunos[i].nome), file);
        fwrite(", ", sizeof(char), strlen(", "), file);
        fwrite(alunos[i].cpf, sizeof(char), strlen(alunos[i].cpf), file);
        
        fwrite(&alunos[i].qtd_notas, sizeof(int), 1, file);
        for(int j=0; j<alunos[i].qtd_notas; j++){
            fwrite(&alunos[i].notas[j], sizeof(float), 1, file);
        }
    }

    fclose(file);
}
