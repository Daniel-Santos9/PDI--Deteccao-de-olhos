#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void coletarPontos (string nomeImagem, string pasta1Imagem, string pasta2Imagem, int nPontos, int nImagens, int indiceReferencia);

void coletaPontos_ROC (string pasta1Imagem, int nAmostras, int nImagens);
