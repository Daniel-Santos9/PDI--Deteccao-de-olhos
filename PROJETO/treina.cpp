#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "treina.h"
#include "gravaDados.h"
#include <stdlib.h>

using namespace cv;
using namespace std;

double*** calc_desc(string pasta1Imagem, string pasta2,  int nImagens, int nAmostras, int altura, int largura, int profundidade) {
    string nomeImagem[10] = {"2.jpg", "imagem1.jpg", "imagem2.jpg", "imagem3.jpg", "imagem4.jpg","imagem5.jpg", "imagem6.jpg", "imagem7.jpg", "imagem8.jpg", "imagem9.jpg"};

	int x, y, z;

	double ***descritores;
	descritores = (double***) malloc( nImagens * sizeof (double**));
	for (int i = 0; i < nImagens; ++i){
		descritores[i] = (double**) malloc( nAmostras * sizeof (double*));
		for (int j = 0; j < nAmostras; ++j){
			descritores[i][j] = (double*) malloc( profundidade * sizeof (double));
		}
	}

    // Bloco 2 >> coletas pontos do Arquivo
        int valor; char espaco;
        int ***pontos;
        pontos = (int***) malloc( nImagens * sizeof (int**));
        for (int i = 0; i < nImagens; ++i){
            pontos[i] = (int**) malloc( nAmostras * sizeof (int*));
            for (int j = 0; j < nAmostras; ++j){
                pontos[i][j] = (int*) malloc( 2 * sizeof (int));
            }
        }


        string caminho = pasta2+"pontos.txt";

        FILE *arq= fopen(caminho.c_str(), "r");	// Cria um arquivo texto para gravação dos pontos

        if (arq == NULL)				// Se nào conseguiu criar
        {
            printf("Problemas na leitura do arquivo de pontos treino\n");
            system("pause");
        } else {
            for (int i = 0; i < nImagens; i++){
                cout<<"Imagem "<<i<<endl;
                for (int j = 0; j < nAmostras; j++){
                    cout<<"Ponto "<<j<<": x=";
                    for (int l = 0; l < 2; ++l){
                        fscanf(arq,"%d%c",&valor,&espaco);
                        pontos[i][j][l] = valor;
                        cout<<pontos[i][j][l];
                        cout<<", y=";
                    }
                    cout<<endl;
                }
                cout<<endl;
            }
            fclose(arq);
        }
    // FIM DE BLOCO 2
    //system("pause");

	for(int indiceReferencia=0; indiceReferencia< nImagens; indiceReferencia++){
		cout<<"imagem   "<<indiceReferencia<<"\n";
		// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)
        string caminho1Imagem = pasta1Imagem+nomeImagem[indiceReferencia];	// Pasta de onde serão buscadas as imagens

        Mat imgCinza =  imread(caminho1Imagem,1);
        if(imgCinza.empty())
		{
            cout <<  "Imagem X nao encontrada" << endl ;
			//return 0;
		}
	// FIM DE BLOCO 1


	// Bloco 3 >> EXTRAI A VINZINHAÇA DE CADA PIXEL REFERENCIADO PELO USUÁRIO

		int** amostras = (int**) malloc(nAmostras * sizeof (int*));
			for (int i = 0; i < nAmostras; ++i)
               amostras[i] = (int*) malloc( 3 * sizeof (int)); // r, g, b


        int x,y;
		for(int i=0; i<nAmostras; i++)
		{
			y = pontos[indiceReferencia][i][0];
			x = pontos[indiceReferencia][i][1];
            cout<<"x="<<x<<" y="<<y<<"\n";
			//system("pause");
            for(int a=0; a<3; a++)
			{

                amostras[i][a] = (int)imgCinza.at<Vec3b>(x,y)[a]; // img.at<Vec3b>(i,j)[a]
                cout<<amostras[i][a]<<" ";
			}
            cout<<endl;
		}
        system("pause");
		//pontos = Liberar_matriz_real(nAmostras, 2, pontos);
		for (int i=0; i < nImagens; i++){ 
			for (int j=0; j<nAmostras; j++) {
				free (pontos[i][j]);  
			}
			free (pontos[i]);
		}
		free (pontos); 
	// FIM DE BLOCO 3
        FILE* arquivo = abrirArquivo("descritores.txt");
        for (int am=0; am<nAmostras; am++){
			x=indiceReferencia;
			y=am;
			for(z=0; z<3; z++){
                descritores[x][y][z]=amostras[y][z];

			}
            if (gravarDadosInt(3, amostras[y], arquivo)==true)
				cout<<"dados salvos em arquivo!\n";
			else cout<<"erro em arquivo de descritores!\n";

		}
		fecharArquivo(arquivo);


	// FIM DE BLOCO 4

	}

    return descritores;

}
	

void treinamento (string nomeImagem, string pasta1, string pasta2, int nPontos, int nImagens, int indiceReferencia){
    int nAmostras = nPontos;
    double ***matriz_desc;
	matriz_desc = (double***) malloc( nImagens * sizeof (double**));
	for (int i = 0; i < nImagens; ++i){
		matriz_desc[i] = (double**) malloc( nAmostras * sizeof (double*));
		for (int j = 0; j < nAmostras; ++j){
			matriz_desc[i][j] = (double*) malloc( 3 * sizeof (double));
		}
	}

    matriz_desc = calc_desc(pasta1, pasta2, nImagens, 40, 10, 40, 3);
	
//--------------------------------------------------------------------------------------------
//	ESTRUTURAS PARA A RNA DO BLOCO 5														  |
//--------------------------------------------------------------------------------------------	
	unsigned long inp=3;        // Numero de entradas da RNA
	unsigned long outp=1;       // Numero de saidas
	double** tr_inp = (double**) malloc( nAmostras * sizeof (double*));									
        for (int i = 0; i < nAmostras; ++i)															
           tr_inp[i] = (double*) malloc( inp * sizeof (double)); // Vetor de entradas para treinamento
																								
	double** tr_out = (double**) malloc( nAmostras * sizeof (double*));										
        for (int i = 0; i < nAmostras; ++i)														
           tr_out[i] = (double*) malloc( outp * sizeof (double)); // Vetor de saidas desejadas	
	
	cout<<"Pressione qualquer tecla para iniciar o refistro de saidas desejadas\n";
	//std::system("pause");
	for(int i=0; i<nAmostras; i++)
    {
		for(int j=0; j<outp; j++)
		{
			//cout<<"Digite a saida desejada do neuronio "<<j<<" para a "<<i+1<<"a. amostra\n";
			//cin>>tr_out[i][j];
			if(i<10)
				tr_out[i][j]=1;
			else
				tr_out[i][j]=0;
		}
	}

	MLP rna; // Cria objeto tipo MLP (rede neural)

    unsigned long hid=3;       // Numero de neuronios escondidos
    unsigned long layers[3];    // Vetor para definição das camadas
    layers[0]=inp;              // Definição da primeira camada (de entradas): 2 elementos
    layers[1]=hid;              // Definição da segunda camada (de neuronios escondidos): 2 elementos
    layers[2]=outp;             // Definição da terceira camada (de neuronios de saida): 1 elemento
    double *outputs;            // Utilizada nos testes
    float taxaAprend = 0.15;   // Taxa de aprendizagem
    unsigned long iter=0;       // Contador de épocas

	//cout<<"Entre com o numero de epocas: ";
    //cin>>iter;
    iter=100;

    rna.SetDataRPROP(layers,3);
    //rna.SetData(taxaAprend, layers,3);

	rna.RandomizeWB();  // Gera pesos aleatorios para pesos e bias

    //rna.carregarPesos("pesos1.txt");
//-----------------------------------------------------------------------------------------


	//if (indiceReferencia<nImagens){	// IF seletor
	
	float perc=0, max=iter-1;
	for(int i=0;i<iter;i++){
		perc=(i*100.0)/max;
		system ("cls"); 
		cout<<perc<<"% concluido (treino).\n";
		
		//cout<<"\nTreinando rede MLP... \n";
	for(int imRef=0; imRef < nImagens; imRef++){
		for(int am=0; am<nAmostras; am++) {
            //cout<<"Ponto "<<am<<"= ";
			for(int j=0; j<3; j++){
                tr_inp[am][j]=matriz_desc[imRef][am][j]/255.0;
            //    cout<<tr_inp[am][j]<<" ";
			}
            //cout<<endl;
            //if(i%1000==0)cout<<"\n"<<i+1<<"a. epoca";
            //erroMedioGlobal=0;
			for(int j=0;j<nAmostras ;j++){
                rna.TrainRPROP(tr_inp[j],tr_out[j],1);
                //rna.Train(tr_inp[j],tr_out[j]); // Treina rede com: Entradas e saidas desejadas
                cout<< rna.ErroMedioIns<<" ";
			}

		}
	  }
	}
    cout<<"Treinamento Finalizado."<<endl;
	rna.salvarPesos("pesos12.txt");

	for (int i = 0; i < nImagens; ++i){
		for (int j = 0; j < nAmostras; ++j){
			free(matriz_desc[i][j]);
		}
		free(matriz_desc[i]);
	}
	free(matriz_desc);
}
