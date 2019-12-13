#ifndef LIMIARIZACAO_H
#define LIMIARIZACAO_H

#include <QImage>
#include <QColor>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int limiar_central(int espectro);

int mean_gray_level(QImage imagem1);

int porc_preto(QImage imagem1);

int tom_medio_cw(int L0, QImage img1);
int tom_medio_cb(int L0, QImage img1);
int limiar_inicial(QImage img1);
int limiar_interativa(QImage img1);

int dois_picos(int * hist);

Mat binariza (Mat img, int L);

#endif // LIMIARIZAÇÃO_H

