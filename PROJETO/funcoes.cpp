#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*bool verifica_cabelo(int pico1, Mat img){ // returna TRUE se as cores das regiões forem semelhantes
    int flag=0, media1=0, media2=0;
    float perc=0;
    Vec3b cor1, cor2;
    for (int j=((img.cols/2)-15);j<((img.cols/2)+15);j++){
        cor1 = img.at<Vec3b>(pico1-20,j);
        media1 += (cor1[2]+cor1[1]+cor1[0])/3;

        cor2 = img.at<Vec3b>(pico1+20,j);
        media2 += (cor2[2]+cor2[1]+cor2[0])/3;
    }

    media1 /= 31;
    media2 /= 31;

    if (media1<media2){
        perc = media1/(float)media2;
    }
    else{
        perc = media2/(float)media1;
    }
    cout<<perc<<endl;
    if (perc<0.83 && perc>0.3){
        flag = 1;
    }
    else {
        flag =0;
    }
    return flag;
}
*/
Mat Sobel_y(Mat img){
    int gx[3][3]={{1,0,-1},{3,0,-3},{1,0,-1}},
        gx2[3][3]={{-1,0,1},{-3,0,3},{-1,0,1}};
    int media,a=1,ga,gb,cor;
    Mat nova=img.clone();
    Vec3b px;

    for(int i=a;i<nova.rows-a;i++){
        for(int j=a;j<nova.cols-a;j++){
            cor = 0;
            ga = 0;
            gb = 0;
            for(int x= -a;x<a+1;x++){

                for(int y=-a;y<a+1;y++){
                    px = img.at<Vec3b>(Point(j+y,i+x));
                    //media= img.at<uchar>(i,j);
                    media = 0.299*px[2] + 0.587*px[1] + 0.114*px[0];
                    ga += media*gx[x+a][y+a];
                    gb += media*gx2[x+a][y+a];
                }

            }

            if(ga>255)
                ga=255;
            if(ga<0)
                ga=0;

            if(gb>255)
                gb=255;
            if(gb<0)
                gb=0;

          nova.at<Vec3b>(Point(j,i))[2] = ga+gb;
          nova.at<Vec3b>(Point(j,i))[1] = ga+gb;
          nova.at<Vec3b>(Point(j,i))[0] = ga+gb;


        }
    }

    return nova;
}
Mat Sobel_x(Mat img){
    int gy[3][3]={{-1,-3,-1},{0,0,0},{1,3,1}},
        gy2[3][3]={{-1,-3,-1},{0,0,0},{1,3,1}};
    int media,a=1,ga,gb,cor;
    Mat nova=img.clone();
    Vec3b px;

    for(int i=a;i<nova.cols-a;i++){
        for(int j=a;j<nova.rows-a;j++){
            cor = 0;
            ga = 0;
            gb = 0;
            for(int x= -a;x<a+1;x++){

                for(int y=-a;y<a+1;y++){
                    px = img.at<Vec3b>(Point(i+y,j+x));
                    //media= img.at<uchar>(i,j);
                    media = 0.299*px[2] + 0.587*px[1] + 0.114*px[0];
                    ga += media*gy2[x+a][y+a];
                    gb += media*gy[x+a][y+a];
                }

            }

           if(ga>255)
                ga=255;
           if(ga<0)
                ga=0;

            if(gb>255)
                gb=255;
            if(gb<0)
                gb=0;

          nova.at<Vec3b>(Point(i,j))[2] = gb+ga;
          nova.at<Vec3b>(Point(i,j))[1] = gb+ga;
          nova.at<Vec3b>(Point(i,j))[0] = gb+ga;
        }
    }

    return nova;
}

Mat Sobel_xy(Mat img){
    Mat x, y, nova = img.clone();
    Vec3b px1, px2;
    x = Sobel_x(img);
    y = Sobel_y(img);

    for(int i=0;i<nova.cols;i++){
        for(int j=0;j<nova.rows;j++){
            px1 = x.at<Vec3b>(Point(i,j));
            px2 = y.at<Vec3b>(Point(i,j));

            nova.at<Vec3b>(Point(i,j)) = px1+px2;
        }
    }

    return nova;
}

int maiorY(int *vet_y,int tamanho){ //maior i
    int maior=-1;
    int indice=0;
    for (int i=1;i<tamanho;i++){
        if (vet_y[i]>maior){
            maior=vet_y[i];
            indice=i;
        }
    }
    return indice;
}

int maiorX(int *vet_x,int tamanho){ //maior j
    int maior=-1;
    int indice=0;
    for (int i=1;i<tamanho;i++){
        if (vet_x[i]>maior){
            maior=vet_x[i];
            indice=i;
        }
    }
    return indice;
}

void vetor_x(Mat img, int *v){
    Vec3b px;
    int cont=0, media;
    for(int j=0;j<img.cols;j++){
        for(int i=0;i<img.rows;i++){
            px = img.at<Vec3b>(i,j);
            media=(px[0]+px[1]+px[2])/3;
            if(media > 128) {
                cont++;
            }
        }
        v[j]=cont;
        cout<<v[j]<<",";
        cont=0;
    }
}

void vetor_y(Mat img, int *v){
    Vec3b px;
    int cont=0, media;
    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            px = img.at<Vec3b>(Point(j,i));
            media=(px[0]+px[1]+px[2])/3;
            if(media > 250) {
                cont++;
            }
        }
        v[i]=cont;
        cont=0;
    }
}

/*void dois_picos_h(Mat img,int *v, int tamanho, int *pico1, int *pico2){
    int maior = -999;


// encontrando o primeiro pico
    int i,j,r=1,aux;
    for(i=tamanho-1; i >= 1; i--)
    {
        for(j=0; j < i ; j++)
        {
            if(v[j]>v[j+1])
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }

    do {
        *pico1 = v[tamanho-r];
        r++;
    }while (! verifica_cabelo(v[tamanho-r],img) ) ;


// encontrando o segundo pico
    maior = -999;
    for(int k=20;k<tamanho-20;k++){
        if( ( pow((k-(*pico1)),2) * v[k] ) > maior ){
            maior = pow((k-(*pico1)),2) * v[k];
            *pico2 = k;
        }
    }


}
*/
void dois_picos_v(int *v, int tamanho, int *pico1, int *pico2){
    int maior = -999;


// encontrando o primeiro pico
    for(int j=2;j<tamanho-2;j++){
        if(v[j]>maior){
            maior = v[j];
            *pico1 = j;
        }
    }


// encontrando o segundo pico
    maior = -999;
    for(int k=20;k<tamanho-20;k++){
        if( ( pow((k-(*pico1)),2) * v[k] ) > maior ){
            maior = pow((k-(*pico1)),2) * v[k];
            *pico2 = k;
        }
    }
}

void dois_picos_POS(int *v, int tamanho, int *pico1, int *pico2){
    int maior = -999;

    int PIres;

// encontrando o primeiro pico
    for(int j=2;j<tamanho-2;j++){
        if(v[j]>maior){
            maior = v[j];
            *pico1 = j;
            PIres = maior;

        }
    }

    //PIres = *pico1;
    cout<<"Pico "<<PIres<<endl;
    maior = -999;
    for(int j=2;j<tamanho-2;j++){
        if(v[j]==PIres){
            for(int i=v[j]+25;i<tamanho-25;i++){
                if(v[i]>maior){
                    maior = v[i];
                    *pico1 = i;

                }

            }
            break;
        }
    }

    cout<<"Pico "<<*pico1;

// encontrando o segundo pico
    maior = -999;
    for(int k=20;k<tamanho-20;k++){
        if( ( pow((k-(*pico1)),2) * v[k] ) > maior ){
            maior = pow((k-(*pico1)),2) * v[k];
            *pico2 = k;
        }
    }


}


int modulo(int x){
    if (x<0)
        x*=-1;
    return x;
}


/* - testar função para formar retangulo no rosto -

                  IDEIA 1

   Se o ponto encontrado tiver v[j]+10 for encontrado mais pixels brancos
   entende-se que ele esta na sobrancelha,passa linha alguns pixels abaixo.
   se não for, é pq ele ja esta no olho entao passa linha algus pixels acima,
   ou cria um intervalo 5 pixel acima e 5 pixel a baixo.

                IDEIA 2

    Fazer a media de pixel acima (PXcim) e pixel abaixo (PXbax)do ponto encontrado
    se PXcim > PXbax passa a linha alguns pixels a cima.

*/

int varre_acima(Mat img, int i, int larg){
    Mat img2 = img.clone();
    int cont1=0, cont2=0, media=0;
    Vec3b cor;
    for(int x=(i-larg/2);x<i;x++){
        for(int y=0;y<img.cols;y++){
            cor=img2.at<Vec3b>(x,y);
            media=(cor[0]+cor[1]+cor[2])/3;

            if(media>=128){
                cont1++;
            }
        }

    }

    for(int x=i;x<(i+larg/2);x++){
        for(int y=0;y<img.cols;y++){
            cor=img2.at<Vec3b>(x,y);
            media=(cor[0]+cor[1]+cor[2])/3;
            if(media>=128){
                cont2++;
            }
        }

    }

    if (cont1>cont2){
        return 1;
    }
    else {
        return 0;
    }
}
