#ifndef TREINA_H
#define TREINA_H


#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#include "mlp.h"
#include <string>

using namespace std;

double*** calc_desc(string pasta1Imagem, string pasta2,  int nImagens, int nAmostras, int altura, int largura, int profundidade);

void treinamento (string nomeImagem, string pasta1, string pasta2, int nPontos, int nImagens, int indiceReferencia);

#endif // TREINA_H
