#include "limiarizacao.h"
#include "histograma.h"
#include <math.h>
#include <QImage>
#include <QColor>

int limiar_central(int espectro){
    return (espectro-1) /2;

}
int limiar_inicial(QImage img1){ // Função auxiliar que calcula L0 para a limiarização interativa

     int media=0, r,g,b;
     QColor Pix;

    for(int i=0; i<img1.width();i++){
        for(int j=0; j<img1.height();j++){
            Pix = img1.pixel(i,j);
            Pix.getRgb(&r,&g,&b);
            media += (r+g+b)/3;
        }
    }

    return media/(img1.width() * img1.height());
}

int tom_medio_cb(int L0, QImage img1){

    int media=0, r,g,b, cb=0, cont_cb=0;
    QColor Pix;

    for(int i=0; i<img1.width();i++){
        for(int j=0; j<img1.height();j++){
            Pix = img1.pixel(i,j);
            Pix.getRgb(&r,&g,&b);
            media = (r+g+b)/3;
            if(media <=L0){
                cb +=media;
                cont_cb ++;
            }

        }
    }

    return cb/cont_cb;
}

int tom_medio_cw(int L0, QImage img1){

    int media=0, r,g,b, cw=0, cont_cw=0;
    QColor Pix;

    for(int i=0; i<img1.width();i++){
        for(int j=0; j<img1.height();j++){
            Pix = img1.pixel(i,j);
            Pix.getRgb(&r,&g,&b);
            media = (r+g+b)/3;
            if(media >L0){
                cw +=media;
                cont_cw ++;
            }

        }
    }

    return cw/cont_cw;
}

int limiar_interativa(QImage img1){
   int L, L0, tb, tw;

   L0 = limiar_inicial(img1);

   do{

       tb = tom_medio_cb(L0, img1);
       tw = tom_medio_cw(L0, img1);

       L = tb+tw/2;

       if(L != L0){
           L0 = L;
           L = -1;
       }

   }while(L !=L0);

   return L;
}

int mean_gray_level(QImage imagem1){
    int maior = -999, menor = 999;
    int r,g,b,media,larg,alt;
    QColor Pix;
    alt = imagem1.height();
    larg = imagem1.width();

    for(int x =0; x < larg ;x++){

        for(int y = 0;y < alt;y++){

            Pix = imagem1.pixel(x,y);
            Pix.getRgb(&r,&g,&b);
            media=(r+g+b)/3;

            if(media<=menor){
                menor = media;
            }
            if(media>=maior){
                maior = media;
            }
        }
    }

    return (maior + menor) /2;

}

int porc_preto(QImage imagem1){

    QColor Pix;
    int r=0,g=0,b=0,media=0,cont_pre,larg=0,alt=0,L=0,qtd_pixel=0;
    float menor , ppreto=0.0;
    alt = imagem1.height();
    larg = imagem1.width();
    qtd_pixel = alt * larg;

    for(int i=0;i<256;i++){
        cont_pre = 0;

        for(int x =0; x < larg ;x++){

            for(int y = 0;y < alt;y++){

                Pix = imagem1.pixel(x,y);
                Pix.getRgb(&r,&g,&b);
                media=(r+g+b)/3;

                if(media<=i){
                    cont_pre++;
                }
            }
        }

        ppreto = (cont_pre / qtd_pixel);

        if(ppreto == 0.1)
            return i;

        if( fabs( ppreto - 0.1 ) < menor ){
            menor = fabs( ppreto - 0.1 );
            L = i;
        }
   }

    return L;

}

int dois_picos(int * hist){
    int maior = -999;
    int pico1=0,pico2=0;

// encontrando o primeiro pico
    for(int j=0;j<256;j++){
        if(hist[j]>maior){
            maior = hist[j];
            pico1 = j;
        }
    }

// encontrando o segundo pico
    maior = -999;
    for(int k=0;k<256;k++){
        if( ( pow((k-pico1),2) * hist[k] ) > maior ){
            maior = pow((k-pico1),2) * hist[k];
            pico2 = k;
        }
    }

    return (pico1+pico2)/2;
}

Mat binariza (Mat img, int L){
    Vec3b px;
    Mat img2 = img.clone();
    int cinza;
    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            px = img.at<Vec3b>(Point(j,i));
            cinza=(px[0]+px[1]+px[2])/3;

            if(cinza<=L){
                img2.at<Vec3b>(Point(j,i))[2] = 0;
                img2.at<Vec3b>(Point(j,i))[1] = 0;
                img2.at<Vec3b>(Point(j,i))[0] = 0;
            }
            else{
                img2.at<Vec3b>(Point(j,i))[2] = 255;
                img2.at<Vec3b>(Point(j,i))[1] = 255;
                img2.at<Vec3b>(Point(j,i))[0] = 255;
            }

        }
    }
    return img2;
}
