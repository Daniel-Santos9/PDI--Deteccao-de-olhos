#include "gravaDados.h"

FILE* abrirArquivo(char* arquivo)
{
	FILE *arq;
	arq = fopen(arquivo, "wt");	// Cria um arquivo texto para gravação
	return arq;
}

bool gravarDados(int n, double *dados, FILE* arq)
{
	int i;
	int result;
	if (arq == NULL)				// Se nào conseguiu criar
	{
		printf("Problemas na CRIACAO do arquivo\n");
		return false;
	}
	for (i = 0; i<n-1;i++)
	{
		// A funcao 'fprintf' devolve o número de bytes gravados 
		// ou EOF se houve erro na gravação
		result = fprintf(arq,"%f\t",dados[i]);  					  
		if (result == EOF)	
		{
			printf("Erro na Gravacao\n");
			return false;
		}
	}
	result = fprintf(arq,"%f\n",dados[n-1]);  					  
	if (result == EOF)	
	{
		printf("Erro na Gravacao\n");
		return false;
	}
	
	return true;
}

bool gravarDadosInt(int n, int *dados, FILE* arq)
{
    int i;
    int result;
    if (arq == NULL)				// Se nào conseguiu criar
    {
        printf("Problemas na CRIACAO do arquivo\n");
        return false;
    }
    for (i = 0; i<n-1;i++)
    {
        // A funcao 'fprintf' devolve o número de bytes gravados
        // ou EOF se houve erro na gravação
        result = fprintf(arq,"%d\t",dados[i]);
        if (result == EOF)
        {
            printf("Erro na Gravacao\n");
            return false;
        }
    }
    result = fprintf(arq,"%d\n",dados[n-1]);
    if (result == EOF)
    {
        printf("Erro na Gravacao\n");
        return false;
    }

    return true;
}

void fecharArquivo(FILE* arq)
{
	fclose(arq);
}
