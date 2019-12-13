#ifndef FUNCOES_H
#define FUNCOES_H
#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


Mat Sobel_x(Mat img);
Mat Sobel_y(Mat img);
Mat Sobel_xy(Mat img);

Mat prew_y(Mat img);
Mat prew_x(Mat img);

void vetor_x(Mat img, int *v);
void vetor_y(Mat img, int *v);

int maiorY(int *vet_y,int tamanho);
int maiorX(int *vet_x,int tamanho);
void dois_picos_h(Mat img,int *v, int tamanho, int *pico1, int *pico2);
void dois_picos_v(int *v, int tamanho, int *pico1, int *pico2);
void dois_picos_POS(int *v, int tamanho, int *pico1, int *pico2);
bool verifica_cabelo(int pico1, Mat img);
int modulo(int x);

int varre_acima(Mat img, int i, int larg);
#endif // FUNCOES_H
