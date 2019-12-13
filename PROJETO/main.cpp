#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <QImage>
#include <QColor>
#include "funcoes.h"
#include <stdlib.h>
#include "meth_otsu.h"
#include "limiarizacao.h"
#include "histograma.h"
#include "coletaPontos.h"
#include "treina.h"
#include "testa.h"

using namespace cv;
using namespace std;

int main(){
    Mat img, nova, nova2;
   // Mat img2(img.rows, img.cols, CV_8UC1);
    //string imagens[10] = {};
    img = imread("10.pgm",1);
    int *vet_x = (int*) malloc(sizeof(int)*img.cols);
    int *vet_y = (int*) malloc(sizeof(int)*img.rows);
    int tamanho;

    if(img.empty()){
        cout<<"img nao encontrada";
        return 0;
    }


    //coletarPontos("2.jpg","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\",20,1,0);
    //treinamento( "2.jpg","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\",20,1,0);
    //executaRNA ("2.jpg","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\","C:\\Users\\Junior\\Desktop\\PROJETO\\BASE\ DE\ IMAGENS\\");
   /* Vec3b px;
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            px = img.at<Vec3b>(i,j);
            img2.at<uchar>(i,j) = 0.299*px[2] + 0.587*px[1] + 0.114*px[0];
        }
    }system("pause");*/
    //equalizeHist(img, img);

    nova = Sobel_x(img);
    nova2 = Sobel_y(img);

    int l1 = metodo_otsu(nova);
    //int l1 = 128;
    nova = binariza(nova, l1);
    int l2 = metodo_otsu(nova2);
    //int l2 = 128;
    nova2 = binariza(nova2, l2);

    int ele_tam=1;
    Mat elemento = getStructuringElement(MORPH_RECT, Size(ele_tam+5, ele_tam+1), Point(ele_tam, ele_tam));
    erode(nova, nova, elemento);
    dilate(nova, nova, elemento);


    vetor_x(nova2, vet_x); //VETOR COLUNA - LARGURA IMAGEM
    vetor_y(nova, vet_y); // VETOR LINHA - ALTURA IMAGEM

    int m1, m2, m3, m4;
    dois_picos_v(vet_x, nova2.cols, &m1, &m2);
    dois_picos_POS(vet_y, nova.rows, &m3, &m4);
    cout<<"linha: "<<m3<<endl;
    if( varre_acima(nova2, m3, (modulo(m1-m2)/4)) ==1){ // retorna 1, se mais pixels acima
        m3 = m3-(modulo(m1-m2)/8);
        m4 = m3 + (modulo(m1-m2)/4);
    }
    else {
        m3 = m3;
        m4 = m3 + (modulo(m1-m2)/4);
    }
    line(nova2, Point(m2, 0), Point(m2, nova2.rows-1),Scalar(0, 0, 255));
    line(nova2, Point(m1, 0), Point(m1, nova2.rows-1),Scalar(0, 0, 255));

    line(nova, Point( 0, m4), Point(nova.cols-1, m4),Scalar(0, 0, 255));
    line(nova, Point(0, m3), Point(nova.cols-1, m3),Scalar(0, 255, 0));

    Mat final = img.clone();

    rectangle(final,  Point(m1, m3), Point(m2, (m3+modulo(m1-m2)/4)), Scalar(0,255,0));

    Mat proc2(  modulo(m3-m4), modulo(m1-m2),CV_8UC3);
    for(int i=0; i<proc2.rows; i++){
        for(int j=0; j<proc2.cols; j++){
            proc2.at<Vec3b>(i,j) = nova2.at<Vec3b>(i+m3,j+m1);
        }
    }

    //proc2 = Sobel_xy(proc2);
    //l1 = metodo_otsu(nova);
    //proc2 = binariza(proc2, l1);

    /*
    ele_tam = 2;
    elemento = getStructuringElement(MORPH_ELLIPSE, Size(ele_tam+3, ele_tam+1), Point(ele_tam, ele_tam));
    dilate(proc2, proc2, elemento);
    erode(proc2, proc2, elemento);

    erode(proc2, proc2, elemento);
    dilate(proc2, proc2, elemento);

    ele_tam = 5;
    elemento = getStructuringElement(MORPH_ELLIPSE, Size(ele_tam+3, ele_tam+1), Point(ele_tam, ele_tam));
    erode(proc2, proc2, elemento);
    dilate(proc2, proc2, elemento);

    dilate(proc2, proc2, elemento);
    erode(proc2, proc2, elemento);
*/
    //namedWindow("Imagem1",1);
    //imshow("Imagem1",nova);
    //namedWindow("Imagem2",1);
    //imshow("Imagem2",nova2);
    namedWindow("ImagemF",1);
    imshow("ImagemF",final);
    //namedWindow("Imagem Original",1);
    //imshow("Imagem Original",img);
    namedWindow("ImagemP",1);
    imshow("ImagemP",proc2);
    waitKey(0);
    //destroyWindow("Imagem1");
    //destroyWindow("Imagem2");
    destroyWindow("ImagemF");
    destroyWindow("ImagemP");
}
