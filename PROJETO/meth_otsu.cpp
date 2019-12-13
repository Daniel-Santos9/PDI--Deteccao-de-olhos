#include "meth_otsu.h"
#include "histograma.h"
#include <math.h>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*Função que calcula a probabilidade do limiar ótimo está contido em C1={0...,k-1)*/
float peso_c1(int k, int * hist, int tam){
    float p1 = 0.0;

    for(int i=0; i<k; i++){
        p1 += hist[i];
    }

    return p1/tam;
}

/* Funções de calculo de total de elementos das classes */
int elem_c1(int k,int * hist){
    int cont=0;

    for(int i=0; i<k; i++){
        cont += hist[i];
    }

   return cont;
}
int elem_c2(int k,int * hist){
    int cont=0;

    for(int i=k; i<256; i++){
        cont += hist[i];
    }

   return cont;
}
/*Funções que calculam a média de cada classe */

/* Cálculo da media da classe C1 */
float media_c1(int * hist, int k){
    float med_c1 = 0.0;

    for(int i=0;i<k;i++){
        med_c1 += i * hist[i];
    }

    return med_c1/elem_c1(k,hist);

}

/* Cálculo da media da classe C2 */
float media_c2(int * hist, int k){
    float med_c2 = 0.0;

    for(int i=k;i<256;i++){
        med_c2 += i * hist[i];
    }

    return med_c2/elem_c2(k,hist);
}

/*Variância - Nada mais é que a indicação do quanto um valor está proximo da media de um grupo
*/

// Função que calcula a variância da Classe C1
float varia_c1(float m1, int * hist,int k){
    float v1 = 0.0;

    for(int i=0; i<k;i++){
        v1 += pow((i - m1),2) * hist[i];
    }
    return v1/elem_c1(k,hist);
}

// Função que calcula a variância da Classe C2

float varia_c2(float m2, int * hist,int k){
    float v2 = 0.0;

    for(int i=k; i<256;i++){
        v2 += pow((i - m2),2) * hist[i];
    }
    return v2/elem_c2(k,hist);
}

// função que procura a menor variância intra-classe e retorna o limiar correspondente a ela (limiar ótimo)

int limiar_otsu(float * vt){
    int menor = 9999, t;

    for(int i=0;i<256;i++){
        if(vt[i]<menor){ // condição que testa se a variância no indice k é menor que a variância contida na variável menor
            menor = vt[i]; // se verdade menor recebe a variância daquele índice e o limiar o indice testado.
            t = i;
        }
    }
    return t; // após percorrer todos os tons de cinza, retorna o limiar que é o indice da menor variância
}

// função principal do método que chama as outras funções auxiliares e retorna o limiar ótimo para o programa.
int metodo_otsu(Mat img){

    int * hist;
    int tam = img.cols * img.rows;
    float p1, p2, m1, m2,v1,v2, * vt;
    vt = (float*)malloc(256*sizeof(float));


    /* Geração do Histograma */
    hist = obter_hist(img);
     /* Geração do vetor de probabilidade de cada nivel de cinza do Histograma */

    for(int k = 0; k <256; k++){
        p1 = peso_c1(k,hist,tam);
        p2 = 1 - p1; /* p1 + p2 = 1,pois p1 + p2 é a soma de todas as probabilidades portanto: p2 = 1 - p1*/
        m1 = media_c1(hist,k);
        m2 = media_c2(hist,k);
        v1 = varia_c1(m1,hist,k);
        v2 = varia_c2(m2,hist,k);
        vt[k] = (p1 * v1) + (p2 * v2); // cálculo da variância intra-classe para cada valor de k (0..., L-1)
    }
    int limiar = limiar_otsu(vt);
    free(hist);
    free(vt);
    return limiar; // retorna o valor do limiar ótimo
}

/* Quanto menor a variância intra-classe maior será a variância inter-classe*/
