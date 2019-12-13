#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "coletaPontos.h"
using namespace cv;
using namespace std;

Mat preta(Mat imagem){
    Mat imagem_dst = imagem.clone();
    int media1;
    Vec3b pix,cor1;
    for(int i=0; i<imagem.rows; i++)
	{
        for(int j=0; j<imagem.cols; j++)
		{

            cor1 = imagem_dst.at<Vec3b>(i,j);
            media1 += (cor1[2]+cor1[1]+cor1[0])/3;


            if(media1<=150){
                pix[0] = (0);
                pix[1] = (0);
                pix[2] = (0);
                imagem_dst.at<Vec3b>(i,j) = pix;
                //cvSet2D(imagem_dst,i,j,pix);
			}
			else{
                pix[0] = (255);
                pix[1] = (255);
                pix[2] = (255);
                imagem_dst.at<Vec3b>(i,j) = pix;
                //cvSet2D(imagem_dst,i,j,pix);
			}
		}
	}
	return imagem_dst;
}

int gX, gY;
void onMouse( int event, int x, int y, int flags, void *param){
    Mat *img = (Mat*) param;
    if( event != CV_EVENT_LBUTTONDOWN )
        return;

    //int pix = (int)cvGetReal2D(param, y, x);

    Vec3b pix = (*img).at<Vec3b>(x,y); //Outro jeito de pegar RGB


    printf("Posicao: y=%d x=%d, Valor RGB=%d,%d,%d\n",y,x,pix[2], pix[1], pix[0]);
    gX=x;
    gY=y;
    destroyWindow("Definir ex");

}
void getExemplo(Mat img){
    Mat img2(img);
	cv::namedWindow("Definir ex", CV_WINDOW_AUTOSIZE);
    cv::setMouseCallback("Definir ex", onMouse, &img);
	cv::imshow("Definir ex", img2);
    cv::waitKey(0);
}

void coletarPontos (string nomeImagem, string pasta1Imagem, string pasta2Imagem, int nPontos, int nImagens, int indiceReferencia) {

	if (indiceReferencia<nImagens){	// IF seletor

// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)	
	string caminho1Imagem = pasta1Imagem+nomeImagem;	// Pasta de onde serão buscadas as imagens
    string caminho2Imagem = pasta2Imagem+nomeImagem;	// Pasta onde as images serao salvas

    Mat imgCinza = imread(caminho1Imagem,1);
    if(imgCinza.empty())
    {
        cout <<  "Imagem nao encontrada" << std::endl ;
        return;
    }
// FIM DE BLOCO 1

// Bloco 2 >> CARREGA A ORIENTAÇÃO DOS PIXEL COLETADOS PELO USUÁRIO	
	int nAmostras = nPontos;
	int **pontos;
    pontos = (int**) malloc( nAmostras * sizeof (int*));
        for (int i = 0; i < nAmostras; ++i)
           pontos[i] = (int*) malloc( 2 * sizeof (int));

    for(int i=0; i<nAmostras; i++)
    {
        getExemplo(imgCinza);
        pontos[i][0] = gY;
        pontos[i][1] = gX;
        cout<<i+1<<"Posicao ("<<pontos[i][0]<<","<<pontos[i][1]<<") salva!\n\n";
    }
// FIM DE BLOCO 2

	FILE *arq;

    string caminho = pasta2Imagem+"pontos.txt";

	arq= fopen(caminho.c_str(), "a");	// Cria um arquivo texto para gravação dos pontos
	if (arq == NULL)				// Se nào conseguiu criar
	{
		printf("Problemas na CRIACAO do arquivo de pontos\n");
		system("pause");
	}
	int result;
	for (int i = 0; i<nAmostras;i++)
	{
		for (int j = 0; j<2;j++)
		{
			// A funcao 'fprintf' devolve o número de bytes gravados 
			// ou EOF se houve erro na gravação
			result = fprintf(arq,"%d\t",pontos[i][j]);
			//cout<<"gravado!\n";
			if (result == EOF)	
			{
				printf("Erro na Gravacao do arquivo de pontos\n");
				system("pause");
			}
		}
	}
	fclose(arq);
	for (int i=0; i<nAmostras; i++) 
		free (pontos[i]); 
	free (pontos);      


	} // IF seletor
}

void coletaPontos_ROC (string pasta1Imagem, int nAmostras, int nImagens){

	string nomeImagem[10] = {"imagem1.jpg", "imagem2.jpg", "imagem3.jpg", "imagem4.jpg","imagem5.jpg", "imagem6.jpg", "imagem7.jpg", "imagem8.jpg", "imagem9.jpg", "imagem10.jpg"};
	
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

        string caminho = pasta1Imagem+"pontos_ROC.txt";

		FILE *arq = fopen(caminho.c_str(), "r");	// Cria um arquivo texto para gravação dos pontos
		if (arq == NULL)				// Se nào conseguiu criar
		{
			printf("Problemas na leitura do arquivo de pontos\n");
			cout << endl << caminho << endl;
			system("pause");
		} else {
			for (int i = 0; i < nImagens; i++){
				for (int j = 0; j < nAmostras; j++){
					for (int l = 0; l < 2; ++l){
						fscanf(arq,"%d%c",&valor,&espaco);
						pontos[i][j][l] = valor;
					}
				}
			}
			fclose(arq);
		}
	// FIM DE BLOCO 2
	
		int x, y, cont=0;
		int* amostras = (int*) malloc(nImagens*nAmostras * sizeof (int));
	// BLOCO 1
		for(int imagem=0; imagem< nImagens; imagem++){
			string caminho1Imagem = pasta1Imagem+nomeImagem[imagem];	// Pasta de onde serão buscadas as imagens
            //IplImage* imgCinza =  cvLoadImage(caminho1Imagem.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            Mat imgCinza = imread(caminho1Imagem,1);
            Vec3b pix;
            if(imgCinza.empty())
			{
                cout <<  "Imagem nao encontrada" << endl ;
				//return 0;
			}

            int cinza=0;

			for(int i=0; i<nAmostras; i++)
			{
                cinza=0;

				y = pontos[imagem][i][0];
				x = pontos[imagem][i][1];

                pix[0]=imgCinza.at<Vec3b>(x,y)[0];
                pix[1]=imgCinza.at<Vec3b>(x,y)[1];
                pix[2]=imgCinza.at<Vec3b>(x,y)[2];
                cinza=(pix[0]+pix[1]+pix[2])/3;

                cout << y <<" "<< x <<": "<<cinza<<endl;
                amostras[cont] = cinza; //(int)cvGetReal2D(imgCinza, y, x);
				cont++;
			}


		}
	// FIM DE BLOCO 1

	// BLOCO 3 - salva dados
		FILE *arq2;

	caminho = pasta1Imagem+"dados_ROC.txt";

	arq2= fopen(caminho.c_str(), "a");	// Cria um arquivo texto para gravação dos pontos
	if (arq2 == NULL)				// Se nào conseguiu criar
	{
		printf("Problemas na CRIACAO do arquivo de pontos\n");
		system("pause");
	}
	int result;
	for(int imagem=0; imagem< cont; imagem++){
		
		// A funcao 'fprintf' devolve o número de bytes gravados 
		// ou EOF se houve erro na gravação
		result = fprintf(arq2,"%d\t",amostras[imagem]);
		//cout<<"gravado!\n";
		if (result == EOF)	
		{
			printf("Erro na Gravacao do arquivo de pontos\n");
			system("pause");
		}
			
	}
	fclose(arq2);
	// FIM DE BLOCO 3
}
