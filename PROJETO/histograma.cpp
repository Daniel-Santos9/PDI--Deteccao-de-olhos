#include "histograma.h"
#include <QImage>
#include <QColor>


void inicializa_hist(int * hist){
    for(int i=0;i<256;i++)
        hist[i]=0;
}

int * obter_hist(Mat img1){
    int * hist;
    hist = (int*)malloc(256*sizeof(int));
    inicializa_hist(hist);

    Vec3b px;
    int media;

    for(int i=0;i<img1.rows;i++){
        for(int j=0;j<img1.cols;j++){
            px = img1.at<Vec3b>(Point(j,i));
            media=(px[0]+px[1]+px[2])/3;
            hist[media]+=1;
        }
    }

    return hist;
}

int * obter_histX(Mat img1){
    int * hist;
    hist = (int*)malloc(256*sizeof(int));
    inicializa_hist(hist);

    Vec3b px;
    int media;

    for(int j=0;j<img1.rows;j++){
        for(int i=0;i<img1.cols;i++){
            px = img1.at<Vec3b>(Point(j,i));
            media=(px[0]+px[1]+px[2])/3;
            hist[media]+=1;
        }
    }

    return hist;
}

float * prob_hist(int tam, int *hist){
    float * hist_prob;
    hist_prob = (float*)malloc(256*sizeof(float));

    for(int i=0; i<256;i++){
       hist_prob[i] = (float) hist[i]/tam;
    }

    return hist_prob;
}

float * prob_acum(float *hist_prob){
    float * hist_acum;
    hist_acum = (float*)malloc(256*sizeof(float));

    hist_acum[0] = hist_prob[0];

    for(int i=1; i<256;i++){
       hist_acum[i] = hist_acum[i-1] + hist_prob[i];
    }

    return hist_acum;

}
