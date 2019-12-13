#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H

#include <QImage>
#include <QColor>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void inicializa_hist(int * hist);
int * obter_hist(Mat img1);
float * prob_hist(int tam, int *hist);
float * prob_acum(float *hist);
int * obter_histX(Mat img1);

#endif // HISTOGRAMA_H
