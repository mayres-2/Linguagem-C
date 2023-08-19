#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100]; // NOME DO ALUNO COM NO MÁXIMO 100 CARACTERES
    char cpf[12];        // CPF DO ALUNO
    int qtdNotas;   // QUANTIDADE DE NOTAS DO ALUNO
    float *notas;   // COLOQUEI NOTAS COMO PONTEIRO POIS SERÁ ALOCADA DINAMICAMENTE
    float media;    // MEDIA DAS NOTAS DE CADA ALUNO
} Aluno;

Aluno *carregaAlunos(int *qtdAlunos) {
    FILE *listaalunos;
    Aluno *alunos = NULL;
    int contagem = 0;
    char c;

    listaalunos = fopen("alunos.txt", "r"); // ABRE O ARQUIVO

    if (listaalunos == NULL){ // MEDIDA DE SEGURANÇA 
        printf("Erro ao abrir arquivo para leitura.\n");
        return NULL;
    }

    // CONTA QUANTAS LINHAS TEM O ARQUIVO
    while ((c = fgetc(listaalunos)) != EOF) {
        if (c == '\n')
        {
            contagem++;
        }
    }
    rewind(listaalunos); // USEI REWIND PARA VOLTAR PRO INICIO DO ARQUIVO.

    // ALOCA DINAMICAMENTE UMA VARIAVEL TEMP, COMO MEDIDA DE SEGURANÇA, PARA POSTERIORMENTE TRANSFERIR PARA ALUNOS.
    Aluno *temp = (Aluno *)malloc(contagem * sizeof(Aluno));

    if (temp == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }

    alunos = temp;

    // VAMOS DIZER QUE O ARQUIVO TXT CADA LINHA REPRESENTA UM ALUNO E É ESCRITO DA SEGUINTE FORMA: "Felipe Torres, 11033333323" REPRESENTANDO O NOME DO ALUNO E O CPF SEPARADO POR UMA VÍRGULA
    int i = 0;
    while (!feof(listaalunos) && i < contagem) {
        fscanf(listaalunos, "%[^,], %s\n", alunos[i].nome, alunos[i].cpf);
        i++;
    }
    fclose(listaalunos);   // FECHANDO ARQUIVO
    *qtdAlunos = contagem; // RETORNANDO A QUANTIDADE DE ALUNOS QUE VAI SER IGUAL A QUANTIDADE DE LINHAS DO LISTAALUNOS.TXT
    return alunos;         // RETORNA OS ALUNOS ALOCADOS DINAMICAMENTE, USANDO COMO REFERENCIA A QUANTIDADE DE ALUNOS PRESENTE NO ARQUIVO TXT
}

// ESSA FUNÇÃO RETORNARÁ UM VETOR DINAMICO DE FLOAT COM AS NOTAS E A QUANTIDADE DE NOTAS UM ALUNO.
float *leNotas(int *qtdNotas) {
    float *notas = NULL;
    *qtdNotas = 0;
    float notaatual;
    int i = 1; //VARIAVEL "i" SERVE SÓ PRA PRINTAR QUAL NOTA DO ALUNO O USUARIO DEVE DIGITAR
    printf("Digite a %d nota: \n", i); //DIGITA PRIMEIRA NOTA
    scanf("%f", &notaatual);
    while (notaatual > 0) {
        notas = (float *)realloc(notas, (*qtdNotas + 1) * sizeof(float));
        if (notas == NULL){
            exit(1);
        }
        notas[*qtdNotas] = notaatual;
        (*qtdNotas)++;
        i++;
        printf("Digite a %d nota: \n", i);
        scanf("%f", &notaatual); // DIGITA SEGUNDA NOTA
    }
    return notas;
}

// ESSA FUNÇÃO RETORNARÁ UM VALOR FLOAT COM A MÉDIA DE UM ALUNO.
float media(float *notas, int qtdNotas) {
    float soma = 0;
    for (int i = 0; i < qtdNotas; i++) {
        soma += notas[i];
    }
    return (soma / qtdNotas);
}

// ORDENA USANDO O ALGORITMO DE BUBBLE SORT OS ALUNOS EM ORDEM DECRESCENTE
void ordena(Aluno *alunos, int qtdAlunos) {
    Aluno cache;
    for (int i = 0; i < qtdAlunos; i++){
        for (int j = 1; j < qtdAlunos; j++){
            if (alunos[j - 1].media < alunos[j].media){
                cache = alunos[j];
                alunos[j] = alunos[j - 1];
                alunos[j - 1] = cache;
            }
        }
    }
}

// SALVA CADA STRUCT DE ALUNO EM UM ARQUIVO BINÁRIO!
void salvaAlunos(Aluno *alunos, int qtdAlunos){
    FILE *bin;
    if ((bin = fopen("alunos.bin", "wb")) != NULL){
        for (int i = 0; i < qtdAlunos; i++){
            fwrite(&(alunos[i]), sizeof(Aluno), 1, bin);
        }
        fclose(bin);
    }
    else {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
}

int main() {
    Aluno *alunos = NULL;
    int qtdAlunos = 0;
    int choice;
    while (1) {
        //MENU SIMPLES
        printf("= = = MENU = = =\nDIGITE 1 PARA CARREGAR ALUNOS\nDIGITE 2 PARA LER AS NOTAS DOS ALUNOS\nDIGITE 3 PARA CALCULAR A MEDIA DE CADA ALUNO\nDIGITE 4 PARA ORDENAR OS ALUNOS EM MEDIA DECRESCENTE\nDIGITE 5 PARA SALVAR EM ARQUIVO EM .BIN\nDIGITE 6 PARA SAIR :(\n");
        scanf("%d", &choice);
        if (choice == 1) {
            // CARREGA DO ARQUIVO TXT OS NOMES E CPF DOS ALUNOS
            alunos = carregaAlunos(&qtdAlunos);
            if (carregaAlunos(&qtdAlunos) == NULL){
                printf("Erro ao puxar arquivo txt!! Verifique se o arquivo está txt está na pasta\n");
                free(alunos);
                exit(1);
            }
            else{
                printf("ALUNOS CARREGADOS COM SUCESSO!\n");
            }
        }
        else if (choice == 2){
            // NESSE PASSO EU PEGO CADA ALUNO QUE ESTÁ ALOCADO DINAMICAMENTE E PEÇO PARA O USUARIO DIGITAR AS NOTAS DE CADA ALUNO!
            for (int i = 0; i < qtdAlunos; i++)
            {
                alunos[i].notas = leNotas(&alunos[i].qtdNotas);
                if (leNotas(&alunos[i].qtdNotas) == NULL)
                {
                    printf("ERRO!!\n");
                    free(alunos);
                    exit(1);
                }
            }
        }
        else if (choice == 3){
            // CALCULA A MÉDIA DE CADA ALUNO E COLOCA DENTRO DA STRUCT ALUNO.
            for (int i = 0; i < qtdAlunos; i++)
            {
                alunos[i].media = media(alunos[i].notas, alunos[i].qtdNotas);
            }
            printf("MÉDIA CALCULA COM SUCESSO!!\n");
        }
        else if (choice == 4){
            // ORDENA OS ALUNOS EM FORMA DECRESCENTE DE MÉDIA
            ordena(alunos, qtdAlunos);
            printf("ALUNOS ORDENADOS EM FORMA DECRESCENTE COM SUCESSO!\n");
        }
        else if (choice == 5){
            // SALVA CASA STRUCT DO VETOR DINAMICO DE ALUNOS EM UM ARQUIVO BINÁRIO
            salvaAlunos(alunos, qtdAlunos);
            printf("ARQUIVO .BIN CRIADO COM SUCESSO!!\n");
        }
        else if (choice == 6){
            // FINALIZA O PROGAMA
            free(alunos);
            return 0;
        }
        else{
            printf("OPCAO INVALIDA!! DIGITE NOVAMENTE\n");
        }
        
    }

    return 0;
}