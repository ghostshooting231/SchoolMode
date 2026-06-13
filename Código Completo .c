#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

#define MAX_ESTUDANTES 100

 

// ==========================================

// 1. ESTRUTURA DE DADOS

// ==========================================

typedef struct {

    int matricula;

    char nome[50];

    float nota;

} Estudante;

 

// ==========================================

// 2. MODULO DE MANIPULAÇÃO DE FICHEIROS

// ==========================================

 

// Lê dados de um ficheiro de texto (ex: estudantes.txt)

int lerFicheiroTexto(Estudante estudantes[], const char *nomeFicheiro) {

    FILE *ficheiro = fopen(nomeFicheiro, "r");

    if (ficheiro == NULL) {

        printf("\n[ERRO] Nao foi possivel abrir o ficheiro '%s' para leitura.\n", nomeFicheiro);

        return 0;

    }

 

    int i = 0;

    // Formato esperado no ficheiro: matricula,nome,nota (um por linha, sem espaços no nome substituídos por '_')

    while (fscanf(ficheiro, "%d,%[^,],%f\n", &estudantes[i].matricula, estudantes[i].nome, &estudantes[i].nota) != EOF) {

        i++;

        if (i >= MAX_ESTUDANTES) {

            printf("\n[AVISO] Limite maximo de %d estudantes atingido em memoria.\n", MAX_ESTUDANTES);

            break;

        }

    }

 

    fclose(ficheiro);

    printf("\n[SUCESSO] %d estudantes carregados a partir do ficheiro de texto!\n", i);

    return i;

}

 

// Grava os dados em ficheiro de Texto ou Binário

void gravarFicheiro(Estudante estudantes[], int n, const char *nomeFicheiro, int tipo) {

    if (n == 0) {

        printf("\n[AVISO] Nao ha dados em memoria para gravar.\n");

        return;

    }

 

    if (tipo == 1) { // Texto

        FILE *ficheiro = fopen(nomeFicheiro, "w");

        if (ficheiro == NULL) {

            printf("\n[ERRO] Erro ao criar o ficheiro de texto '%s'.\n", nomeFicheiro);

            return;

        }

        for (int i = 0; i < n; i++) {

            fprintf(ficheiro, "%d,%s,%.2f\n", estudantes[i].matricula, estudantes[i].nome, estudantes[i].nota);

        }

        fclose(ficheiro);

        printf("\n[SUCESSO] Dados gravados em formato TEXTO no ficheiro '%s'.\n", nomeFicheiro);

    } 

    else if (tipo == 2) { // Binário

        FILE *ficheiro = fopen(nomeFicheiro, "wb");

        if (ficheiro == NULL) {

            printf("\n[ERRO] Erro ao criar o ficheiro binario '%s'.\n", nomeFicheiro);

            return;

        }

        fwrite(estudantes, sizeof(Estudante), n, ficheiro);

        fclose(ficheiro);

        printf("\n[SUCESSO] Dados gravados em formato BINARIO no ficheiro '%s'.\n", nomeFicheiro);

    }

}

 

// ==========================================

// 3. MÓDULO DE ALGORITMOS DE ORDENAÇÃO

// ==========================================

 

// Bubble Sort: Ordena por Matrícula (Ordem Crescente)

void bubbleSortMatricula(Estudante estudantes[], int n) {

    int i, j;

    Estudante temp;

    for (i = 0; i < n - 1; i++) {

        for (j = 0; j < n - i - 1; j++) {

            if (estudantes[j].matricula > estudantes[j + 1].matricula) {

                temp = estudantes[j];

                estudantes[j] = estudantes[j + 1];

                estudantes[j + 1] = temp;

            }

        }

    }

    printf("\n[ORDENACAO] Lista ordenada por Matricula (Crescente) via Bubble Sort.\n");

}

 

// Selection Sort: Ordena por Nome (Ordem Alfabética)

void selectionSortNome(Estudante estudantes[], int n) {

    int i, j, minIdx;

    Estudante temp;

    for (i = 0; i < n - 1; i++) {

        minIdx = i;

        for (j = i + 1; j < n; j++) {

            if (strcmp(estudantes[j].nome, estudantes[minIdx].nome) < 0) {

                minIdx = j;

            }

        }

        if (minIdx != i) {

            temp = estudantes[i];

            estudantes[i] = estudantes[minIdx];

            estudantes[minIdx] = temp;

        }

    }

    printf("\n[ORDENACAO] Lista ordenada por Nome (Alfabetica) via Selection Sort.\n");

}

 

// Insertion Sort: Ordena por Nota (Ordem Decrescente)

void insertionSortNota(Estudante estudantes[], int n) {

    int i, j;

    Estudante chave;

    for (i = 1; i < n; i++) {

        chave = estudantes[i];

        j = i - 1;

        // Ordem decrescente: move os elementos menores que a chave para a direita

        while (j >= 0 && estudantes[j].nota < chave.nota) {

            estudantes[j + 1] = estudantes[j];

            j = j - 1;

        }

        estudantes[j + 1] = chave;

    }

    printf("\n[ORDENACAO] Lista ordenada por Nota (Decrescente) via Insertion Sort.\n");

}

 

// ==========================================

// 4. MÓDULO DE ALGORITMOS DE PESQUISA

// ==========================================

 

// Pesquisa Linear por Nome

int pesquisaLinearNome(Estudante estudantes[], int n, const char *nomeProcurado) {

    for (int i = 0; i < n; i++) {

        if (strcmp(estudantes[i].nome, nomeProcurado) == 0) {

            return i; // Retorna o índice do estudante encontrado

        }

    }

    return -1; // Não encontrado

}

 

// Pesquisa Linear por Matrícula

int pesquisaLinearMatricula(Estudante estudantes[], int n, int matriculaProcurada) {

    for (int i = 0; i < n; i++) {

        if (estudantes[i].matricula == matriculaProcurada) {

            return i;

        }

    }

    return -1;

}

 

// Pesquisa Binária por Matrícula (Exige que o vetor esteja previamente ordenado por matrícula!)

int pesquisaBinariaMatricula(Estudante estudantes[], int n, int matriculaProcurada) {

    int inicio = 0;

    int fim = n - 1;

 

    while (inicio <= fim) {

        int meio = inicio + (fim - inicio) / 2;

 

        if (estudantes[meio].matricula == matriculaProcurada) {

            return meio;

        }

        if (estudantes[meio].matricula < matriculaProcurada) {

            inicio = meio + 1;

        } else {

            fim = meio - 1;

        }

    }

    return -1;

}

 

// ==========================================

// 5. FUNÇÕES AUXILIARES DE INTERFACE

// ==========================================

void exibirLista(Estudante estudantes[], int n) {

    if (n == 0) {

        printf("\nA lista esta vazia.\n");

        return;

    }

    printf("\n==================== LISTA DE ESTUDANTES ====================\n");

    printf("%-12s | %-30s | %-5s\n", "Matricula", "Nome do Estudante", "Nota");

    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("%-12d | %-30s | %-5.2f\n", estudantes[i].matricula, estudantes[i].nome, estudantes[i].nota);

    }

    printf("=============================================================\n");

}

 

void exibirEstudante(Estudante est) {

    printf("\n--- Estudante Encontrado ---");

    printf("\nMatricula: %d", est.matricula);

    printf("\nNome     : %s", est.nome);

    printf("\nNota     : %.2f\n", est.nota);

}

 

// ==========================================

// 6. PROGRAMA PRINCIPAL (MENU INTERATIVO)

// ==========================================

int main() {

    Estudante estudantes[MAX_ESTUDANTES];

    int totalEstudantes = 0;

    int opcao, subOpcao, buscaInt, resultadoIdx;

    char buscaStr[50];

    char nomeFicheiro[100];

    int listaEstaOrdenadaPorMatricula = 0; // Flag para controlo da pesquisa binária

 

    do {

        printf("\n=================================================");

        printf("\n  SISTEMA DE GESTAO DE ESTUDANTES - UKV 2026     ");

        printf("\n=================================================");

        printf("\n1. Ler Ficheiro de Texto (Carregar Dados)");

        printf("\n2. Ordenar Lista de Estudantes");

        printf("\n3. Pesquisar Estudante");

        printf("\n4. Gravar Dados Atualizados em Ficheiro");

        printf("\n5. Exibir Lista Atual em Memoria");

        printf("\n0. Sair do Programa");

        printf("\n=================================================");

        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

 

        switch (opcao) {

            case 1:

                printf("\nDigite o nome do ficheiro de origem (ex: estudantes.txt): ");

                scanf("%s", nomeFicheiro);

                totalEstudantes = lerFicheiroTexto(estudantes, nomeFicheiro);

                listaEstaOrdenadaPorMatricula = 0; // Reseta o estado de ordenação ao ler novo arquivo

                break;

 

            case 2:

                if (totalEstudantes == 0) {

                    printf("\n[AVISO] Primeiro deve carregar dados (Opcao 1).\n");

                    break;

                }

                printf("\n--- Criterios de Ordenacao ---");

                printf("\n1. Por Matricula (Crescente) - Bubble Sort");

                printf("\n2. Por Nome (Alfabetica) - Selection Sort");

                printf("\n3. Por Nota (Decrescente) - Insertion Sort");

                printf("\nEscolha o criterio: ");

                scanf("%d", &subOpcao);

 

                if (subOpcao == 1) {

                    bubbleSortMatricula(estudantes, totalEstudantes);

                    listaEstaOrdenadaPorMatricula = 1; // Ativa a flag de ordenação por matrícula

                } else if (subOpcao == 2) {

                    selectionSortNome(estudantes, totalEstudantes);

                    listaEstaOrdenadaPorMatricula = 0;

                } else if (subOpcao == 3) {

                    insertionSortNota(estudantes, totalEstudantes);

                    listaEstaOrdenadaPorMatricula = 0;

                } else {

                    printf("\n[ERRO] Criterio invalido!\n");

                }

                exibirLista(estudantes, totalEstudantes);

                break;

 

            case 3:

                if (totalEstudantes == 0) {

                    printf("\n[AVISO] Nao ha estudantes em memoria para pesquisar.\n");

                    break;

                }

                printf("\n--- Metodos de Pesquisa ---");

                printf("\n1. Pesquisa Linear por Nome");

                printf("\n2. Pesquisa Linear por Matricula");

                printf("\n3. Pesquisa Binaria por Matricula (Requer ordenacao por matricula prévia)");

                printf("\nEscolha o metodo: ");

                scanf("%d", &subOpcao);

 

                if (subOpcao == 1) {

                    printf("\nDigite o nome exato do estudante: ");

                    scanf("%s", buscaStr);

                    resultadoIdx = pesquisaLinearNome(estudantes, totalEstudantes, buscaStr);

                } 

                else if (subOpcao == 2) {

                    printf("\nDigite a matricula a pesquisar: ");

                    scanf("%d", &buscaInt);

                    resultadoIdx = pesquisaLinearMatricula(estudantes, totalEstudantes, buscaInt);

                } 

                else if (subOpcao == 3) {

                    if (!listaEstaOrdenadaPorMatricula) {

                        printf("\n[AVISO] A lista nao esta ordenada por matricula. Execute a ordenacao (Opcao 2 -> Criterio 1) primeiro!\n");

                        break;

                    }

                    printf("\nDigite a matricula a pesquisar: ");

                    scanf("%d", &buscaInt);

                    resultadoIdx = pesquisaBinariaMatricula(estudantes, totalEstudantes, buscaInt);

                } 

                else {

                    printf("\n[ERRO] Metodo invalido!\n");

                    break;

                }

 

                // Verifica e exibe o resultado da pesquisa

                if (resultadoIdx != -1) {

                    exibirEstudante(estudantes[resultadoIdx]);

                } else {

                    printf("\n[RESULTADO] Estudante nao encontrado.\n");

                }

                break;

 

            case 4:

                if (totalEstudantes == 0) {

                    printf("\n[AVISO] Nao ha dados em memoria para gravar.\n");

                    break;

                }

                printf("\nDigite o nome do ficheiro de destino (ex: estudantes_saida.txt ou dados.bin): ");

                scanf("%s", nomeFicheiro);

                printf("\n--- Tipo de Formato ---");

                printf("\n1. Gravar como Ficheiro de Texto (.txt)");

                printf("\n2. Gravar como Ficheiro Binario (.bin)");

                printf("\nEscolha o formato: ");

                scanf("%d", &subOpcao);

 

                if (subOpcao == 1 || subOpcao == 2) {

                    gravarFicheiro(estudantes, totalEstudantes, nomeFicheiro, subOpcao);

                } else {

                    printf("\n[ERRO] Formato invalido!\n");

                }

                break;

 

            case 5:

                exibirLista(estudantes, totalEstudantes);

                break;

 

            case 0:

                printf("\nEncerrando o sistema. Bom trabalho acadamico!\n");

                break;

 

            default:

                printf("\n[ERRO] Opcao invalida! Escolha novamente.\n");

        }

    } while (opcao != 0);

 

    return 0;

}

    