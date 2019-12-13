#include "testa.h"

void executaRNA (string nomeImagem, string pasta1, string pasta2){

// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)
    string caminho1Imagem = pasta1+nomeImagem;	// Pasta de onde serão buscadas as imagens
    string caminho2Imagem = pasta2+nomeImagem;	// Pasta onde as images serao salvas

    Mat imgCinza = imread(caminho1Imagem,1);
    if(imgCinza.empty())
    {
        cout <<  "Imagem nao encontrada" << std::endl ;
        return;
    }
// FIM DE BLOCO 1

    int nAmostras=2;

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

    double desc[3];

    MLP rna;

    unsigned long hid=3;       // Numero de neuronios escondidos
    unsigned long layers[3];    // Vetor para definição das camadas
    layers[0]=inp;              // Definição da primeira camada (de entradas): 2 elementos
    layers[1]=hid;              // Definição da segunda camada (de neuronios escondidos): 2 elementos
    layers[2]=outp;             // Definição da terceira camada (de neuronios de saida): 1 elemento
    double *outputs;            // Utilizada nos testes
    float taxaAprend = 0.35;   // Taxa de aprendizagem
    unsigned long iter=0;       // Contador de épocas

    rna.SetDataRPROP(layers,3);
    rna.RandomizeWB();  // Gera pesos aleatorios para pesos e bias

    string caminho = pasta2+"pesos12.txt";
    rna.carregarPesos(caminho.c_str());

    Mat img2 = imgCinza.clone();

    Vec3b pix;

    //system("pause");

    cout<<"total de linhas: "<<imgCinza.rows<<endl;
    for (int i=0; i<imgCinza.rows; i++){
        //cout<<"linha: "<<i<<endl;
        for (int j=0; j<imgCinza.cols; j++){
            for(int a=0; a<3; a++)
            {
                desc[a] = (int)imgCinza.at<Vec3b>(i,j)[a]; // img.at<Vec3b>(i,j)[a]
            }

            for(int a=0; a<3; a++)
                tr_inp[0][j]=desc[a]/255.0;

            rna.SetInputs(tr_inp[0]);

            outputs = rna.GetOutput();

            pix[0] = (int) (outputs[0]*255);

            //cout<<"cor "<<(outputs[0]*255) ;

            if (pix[0]<0) pix[0]=0;
            if (pix[0]>255) pix[0]=255;

            pix[2]=pix[0];
            pix[1]=pix[0];

            img2.at<Vec3b>(i,j)=pix;
        }

    }



    namedWindow("testado");
    imshow("testado", img2);
    waitKey(0);
    destroyWindow("testado");
}

