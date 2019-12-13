#ifndef METH_OTSU_H
#define METH_OTSU_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <QImage>

using namespace cv;
using namespace std;


// Método principal, responsável por chamar as funções auxiliares e retornar o limiar

    int metodo_otsu(Mat img);

// Função que retorna o limiar ótimo para a função principal baseado na menor variação intra-classe

    int limiar_otsu(float * vt);

// Funções que contam a quantidade elementos de cada classe
    //Elementos C1
        int elem_c1(int k,int * hist);
    //Elementos C2
        int elem_c2(int k,int * hist);

// Função que calcula o peso de cada classe C1, que é a probabilidade
// do limiar ótimo pertencer a ela.

    // Calcula P1
        float peso_c1(int k, int * hist, int tam);

// Funções que calculam as medias das probabilidade de cada classe
// que é o somátório da quantidade de tom de cinza de cada classe multiplicado
// pelo valor do indice dividido pelo total de elementos de sua respectiva classe.

    // Calcula M1
        float media_c1(int * hist, int k);
    // Calcula M2
        float media_c2(int * hist, int k);

// Funções que calculam as variâncias de cada classe

    // Calcula V1
        float varia_c1(float m1, int * hist,int k);
    // Calcula V2
        float varia_c2(float m2, int * hist,int k);

#endif // METH_OTSU_H
