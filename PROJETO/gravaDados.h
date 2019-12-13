#include <stdio.h>

FILE* abrirArquivo(char* arquivo);
bool gravarDados(int n, double *dados, FILE* arq);
bool gravarDadosInt(int n, int *dados, FILE* arq);
void fecharArquivo(FILE* arq);
