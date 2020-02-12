#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <math.h>
#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "functions.h"
#define TAM 100
using namespace std;
using namespace cv;

Mat img;
Mat img_gray;
int dimension = 0;
bool existe_img = false;
string title="",description="";
Mat Original;
Mat Respaldo;
Mat Grises, intermedio;
Mat Resp;
Mat Guardar;
Mat Cuadro(300, 1000, CV_8UC3);
string s;
int limitC=50;
int limitAnt=0;
int uno=0, dos=100;
int nCanales;
int nR;
int nC;
int infeior_alpha = 20;
int superior_alpha = 45;
int xpos, ypos;
int xpos2, ypos2;
int dis=0;
double Matrix[TAM][3]={{0,0,0}};
int pixels[TAM][2]={{0,0}};

double cov[3][3] = {0.0};
double inv[3][3] = {0.0};
double Y[3] = {0.0};
int cont = 0;
int colores = 0;
int bandera = 0;






void inverse(double m[3][3], double minv[3][3]){
    double det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                 m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                 m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    double invdet = 1 / det;


    minv[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
    minv[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
    minv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
    minv[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
    minv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
    minv[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
    minv[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
    minv[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
    minv[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;

    double maxi = 0.0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            if (maxi < minv[i][j]){
                maxi = minv[i][j];
            }
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            minv[i][j] = minv[i][j]/maxi;
        }
    }
}

void covarianza(double mat[TAM][3], int tam, double cov[3][3]){
    double media[3]={0.0};
    double suma = 0.0;
    double varianza = 0.0;
    double Vari[3] = {0.0};
    double medias[tam][3] = {0.0};
    double productos[tam][3] ={0.0};
    double sumapro[3] = {0.0};
    

    for (int i=0; i<3; i++){
        suma = 0.0;
        for(int j=0; j<tam; j++){
            suma+=mat[j][i];
        }
        media[i]=(suma*1.0)/tam;
    }

    for (int i=0; i<3; i++){
        varianza = 0.0;
        suma = 0.0;
        for(int j=0; j<tam; j++){
            varianza = pow((mat[j][i] - media[i]), 2.0);
            suma +=varianza;
        } 
        Vari[i]=(suma*1.0)/(tam-1);
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<tam; j++){
            medias[j][i] = mat[j][i]-media[i];
        }
    }
    for(int j=0; j<tam; j++){
        productos[j][0] = medias[j][0]*medias[j][1];
        productos[j][1] = medias[j][0]*medias[j][2];
        productos[j][2] = medias[j][1]*medias[j][2];
    }
    for (int i=0; i<3; i++){
        suma = 0.0;
        for(int j=0; j<tam; j++){
            suma += productos[j][i];
        }
        sumapro[i] = (suma)/(tam -  1);
    }
    cov[0][0] = Vari[0];
    cov[1][1] = Vari[1];
    cov[2][2] = Vari[2];
    cov[0][1] = cov[1][0] = sumapro[0];
    cov[2][0] = cov[0][2] = sumapro[1];
    cov[2][1] = cov[1][2] = sumapro[2];
}
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN ){
        xpos = x; ypos=y;
        Point3_<uchar>* p = Original.ptr<Point3_<uchar> >(ypos,xpos);
        pixels[cont][0] = xpos;
        pixels[cont][1] = ypos;
        //Matrix[cont][0] = (double) p->x;
        //Matrix[cont][1] = (double) p->y;
        //Matrix[cont][2] = (double) p->z;
        cont++;
        if(cont==2){
            std::system("clear");
            printf("Seleccione n puntos y presione c para segmentar\n");
        }
        if(cont >= 2){
            if(cont>2){
                Matrix[cont-3][0] = (double) p->x;
                Matrix[cont-3][1] = (double) p->y;
                Matrix[cont-3][2] = (double) p->z;
                printf("%d B: %d  G:%d   R:%d\n", cont-2, p->x, p->y, p->z);
                //
                
                    if(dos<=300){
                        rectangle(Cuadro,Point(limitAnt, uno),Point(limitC,dos),Scalar(p->x, p->y, p->z),CV_FILLED);    
                        limitAnt=limitC;
                    }
                        limitC+=50;
                    if (limitC == 1050){
                        limitAnt=0; 
                        limitC=50;
                        uno=dos;
                        dos+=100;
                    }
                

                    
                cv::imshow("Cuadro", Cuadro);
                
                //cv::imshow("Cuadro", Cuadro);
                //

            }
            Original.copyTo(Resp);
            int xmax=0,xmin=nC*nCanales;
            int ymax=0,ymin=nR;
            for (int i = 0; i < cont; i++){
                xmax = max(xmax,pixels[i][0]);
                ymax = max(ymax,pixels[i][1]);
                xmin = min(xmin,pixels[i][0]);
                ymin = min(ymin,pixels[i][1]);   
            }
            rectangle(Resp,Point(xmin,ymin),Point(xmax,ymax),Scalar(255,255,255),2,8);
            imshow("Original",Resp);
        }
    }

    else if  ( event == EVENT_RBUTTONDOWN ){
        cv::imwrite("Segmentado.jpg", Guardar);
        
    }
}

void CallBackFunc2(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN ){
        xpos2 = x; ypos2=y;
        Point3_<uchar>* p = Cuadro.ptr<Point3_<uchar> >(ypos2,xpos2);
       // printf("toca: %d B: %d  G:%d   R:%d\n", cont-2, p->x, p->y, p->z);
        
        int contador = -1;
        double Matrix2[TAM][3]={{0}};
        for(int i= 0; i<cont-2; i++){
            
            if(Matrix[i][0] == p->x && Matrix[i][1] == p->y && Matrix[i][2] == p->z){
                //printf("es %d\n", i);
                contador = i;
                break;
            }
            
            
        }

        if(contador != -1){
            
            rectangle(Cuadro,Point(0, 0),Point(1000, 300),Scalar(255, 255, 255),CV_FILLED);
            cv::imshow("Cuadro", Cuadro);

            //printf("here we go with %d\n", contador);

            for(int i=0; i<cont-2;i++){
                //printf("%.1f %.1f %.1f", Matrix[i][0], Matrix[i][1], Matrix[i][2]);
                
                //printf("\n");
            }
            //printf("------\n");
            int ii=0; int bandi=0;
            for(int i=0; i<cont-2;i++){
                for(int j=0; j<3; j++){
                    if(i!=contador){
                        Matrix2[ii][j] = Matrix[i][j];
                        bandi = 1;
                    }
                }
                if (bandi)
                    ii++;
                bandi = 0;
                
            }
            for(int i=0; i<cont-2;i++){
                Matrix[i][0] =0; Matrix[i][1]=0; Matrix[i][2]=0;
            }
            cont--;

            for(int i=0; i<cont-2;i++){
                Matrix[i][0] = Matrix2[i][0]; Matrix[i][1]=Matrix2[i][1]; Matrix[i][2]=Matrix2[i][2];
            }

            for(int i=0; i<cont-2;i++){
                printf("%.1f %.1f %.1f", Matrix[i][0], Matrix[i][1], Matrix[i][2]);
                
                printf("\n");
            }

            limitC=50;
            limitAnt=0;
            uno=0;
            dos=100;
            for(int i=0; i<cont-2; i++){
                if(dos<=300){
                    rectangle(Cuadro,Point(limitAnt, uno),Point(limitC,dos),Scalar(Matrix[i][0], Matrix[i][1], Matrix[i][2]),CV_FILLED);    
                    limitAnt=limitC;
                    
                }
                limitC+=50;
                if (limitC == 1050){
                    limitAnt=0; 
                    limitC=50;
                    uno=dos;
                    dos+=100;
                }
                cv::imshow("Cuadro", Cuadro);
            }
        }
        
    }
}

void mean(double Matrix[TAM][3], int tam, double Y[3]){
    double suma=0.0;
    for(int i=0; i<3; i++){
        suma=0.0;
        for(int j=0; j<tam; j++){
            suma+=Matrix[j][i];
        }
        Y[i] = ((suma*1.0)/(double)tam);
    }
}
void multiply1(double mat1[1][3], double mat2[3][3], double res[1][3]){ 
    int x, i, j; 
    int m1 = 1, m2=3, n1=3, n2=3;
    for (i = 0; i < m1; i++){ 
        for (j = 0; j < n2; j++){ 
            *(*(res + i) + j) = 0; 
            for (x = 0; x < n1; x++)  
            { 
                *(*(res + i) + j) += *(*(mat1 + i) + x) * 
                                     *(*(mat2 + x) + j); 
            } 
        } 
    } 
} 

void multiply2(double mat1[1][3], double mat2[3][1], double res[1][1]){ 
    int x, i, j; 
    int m1 = 1, m2=3, n1=3, n2=1;
    double sum = 0.0;
    for (i = 0; i < m1; i++)  
    { 
        for (j = 0; j < n2; j++)  
        {
            for (x = 0; x < n1; x++)  
            { 
                sum += *(*(mat1 + i) + x) * 
                                     *(*(mat2 + x) + j); 
            }
            *(*(res + i) + j) = sum;
            sum = 0.0;  
        } 
    } 
} 

void DMah(int v, void *Datos){
        double Mahalanobis = 0;
        double X[3]={0.0};
        double Primero[1][3]={0.0};
        double Segundo[3][1]={0.0};
        double temp[1][3] = {0.0};
        double last[1][1]={0.0};
        int i, j;
        double dd = (double)v;
        for (j = 0; j < nR; j++) {
            uchar* renglon = Respaldo.ptr <uchar>(j);
            uchar* renglon2 = Grises.ptr <uchar>(j);
            for (i = 0; i < nC; i += nCanales) {
                X[0]=*(renglon + i); X[1]=*(renglon + i + 1); X[2]=*(renglon + i + 2);
                for(int k=0; k<3; k++){
                    Primero[0][k] = X[k] - Y[k];
                    Segundo[k][0] = X[k] - Y[k];
                }
                multiply1(Primero, inv, temp);
                multiply2(temp, Segundo, last);
                Mahalanobis = sqrt(last[0][0]);
                if(Mahalanobis>=dd){
                    *(renglon + i) = *(renglon2 + i );
                    *(renglon + i + 1) = *(renglon2 + i + 1);
                    *(renglon + i + 2) = *(renglon2 + i + 2);
                }
            }
        }
    cv::imshow("Color", Respaldo);
    Guardar = Respaldo.clone();
    Respaldo = Original.clone();
}

void Croma(int v, void *Datos){
        double Cubo = 0;
        double X[3]={0.0};
        int i, j;
        double dd = (double)v;
        for (j = 0; j < nR; j++) {
            uchar* renglon = Respaldo.ptr <uchar>(j);
            uchar* renglon2 = Grises.ptr <uchar>(j);
            
            for (i = 0; i < nC; i += nCanales) {
                Cubo = 0;
                X[0]=*(renglon + i); X[1]=*(renglon + i + 1); X[2]=*(renglon + i + 2);
                for(int k=0; k<3; k++){
                    //printf("cubito %.2f ", Cubo);
                    Cubo += (((X[k]*1.0) / (Y[0] + Y[1] + Y[2])));
                    
                }
                Cubo*=10;
                //printf("\nCUBO: %.3f\n\n", Cubo);
                if(Cubo>=dd){
                    *(renglon + i) = *(renglon2 + i );
                    *(renglon + i + 1) = *(renglon2 + i + 1);
                    *(renglon + i + 2) = *(renglon2 + i + 2);
                }
            }
        }
    cv::imshow("Color", Respaldo);
    Guardar = Respaldo.clone();
    Respaldo = Original.clone();
}

void Cubo(int v, void *Datos){
        double Cubo = 0;
        double X[3]={0.0};
        int i, j;
        double dd = (double)v;
        for (j = 0; j < nR; j++) {
            uchar* renglon = Respaldo.ptr <uchar>(j);
            uchar* renglon2 = Grises.ptr <uchar>(j);
            
            for (i = 0; i < nC; i += nCanales) {
                Cubo = 0;
                X[0]=*(renglon + i); X[1]=*(renglon + i + 1); X[2]=*(renglon + i + 2);
                for(int k=0; k<3; k++){
                    //printf("cubito %.2f ", Cubo);
                    Cubo += abs(X[k] - Y[k]);
                    
                }
                //printf("\nCUBO: %.3f\n\n", Cubo);
                if(Cubo>=dd){
                    *(renglon + i) = *(renglon2 + i );
                    *(renglon + i + 1) = *(renglon2 + i + 1);
                    *(renglon + i + 2) = *(renglon2 + i + 2);
                }
            }
        }
    cv::imshow("Color", Respaldo);
    Guardar = Respaldo.clone();
    Respaldo = Original.clone();
}

void Euclideana(int v, void *Datos){
        double Eu = 0;
        double X[3]={0.0};
        int i, j;
        double dd = (double)v;
        for (j = 0; j < nR; j++) {
            uchar* renglon = Respaldo.ptr <uchar>(j);
            uchar* renglon2 = Grises.ptr <uchar>(j);
            
            for (i = 0; i < nC; i += nCanales) {
                Eu = 0;
                X[0]=*(renglon + i); X[1]=*(renglon + i + 1); X[2]=*(renglon + i + 2);
                for(int k=0; k<3; k++){
                    //printf("cubito %.2f ", Cubo);
                    Eu += sqrt( (X[k] - Y[k]) * (X[k] - Y[k]) );
                    
                }
                //printf("\nCUBO: %.3f\n\n", Cubo);
                if(Eu >= dd){
                    *(renglon + i) = *(renglon2 + i );
                    *(renglon + i + 1) = *(renglon2 + i + 1);
                    *(renglon + i + 2) = *(renglon2 + i + 2);
                }
            }
        }
    cv::imshow("Color", Respaldo);
    Guardar = Respaldo.clone();
    Respaldo = Original.clone();
}









MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AbrirBut_clicked()
{

        QFile file;
        QTextStream io;
        QString file_name;
        String picture_path="";
        //Abrir archivo
        file_name = QFileDialog::getOpenFileName(this,"Abrir");
        file.setFileName(file_name);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        //Ruta de archivo
        picture_path = file_name.toStdString();

        //Lectura de imagen RGB
        img = imread(picture_path, CV_LOAD_IMAGE_COLOR);
        //img_gray = imread(picture_path,0);
        //string nameBN = "img/byn.jpg";
        //imwrite(nameBN,img_gray);

        if(!file.isOpen() || ! img.data )
        {
            QMessageBox::critical(this,"Error","No se pudo abrir archivo");
            return;
        }
        //Cerrar archivo
        io.setDevice(&file);
        file.flush();
        file.close();

        //Renderizar imagen original en interfaz
        QPixmap pix(file_name);
        int w = ui->imgOriginal->width();
        int h = ui->imgOriginal->height();
        ui->imgOriginal->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->imgOriginal->setFrameShape(QFrame::NoFrame);

        

        existe_img = true;
}

void MainWindow::on_cuadradoBut_clicked()
{
    
    if(!existe_img)
    {
        QMessageBox::critical(this,"Error","Debes cargar una imagen");
        return;   
    }

    limitC=50;
    limitAnt=0;
    uno=0, dos=100;
    infeior_alpha = 20;
    superior_alpha = 45;
    dis=0;
    cont = 0;
    colores = 0;
    bandera = 0;
    s.append("S.jpg");
    Original=img.clone();
    nCanales = Original.channels();
    nR = Original.rows;
    nC = Original.cols * nCanales;
    
    //cv::cvtColor(Original, intermedio, CV_BGR2GRAY);
    //cv::cvtColor(intermedio, Grises, CV_GRAY2BGR);
    cv::cvtColor(Original, intermedio, COLOR_BGR2GRAY);
    cv::cvtColor(intermedio, Grises, COLOR_GRAY2BGR);

    Respaldo = Original.clone();
    Guardar = Respaldo.clone();

    //Mat Cuadro(100, 1000, CV_8UC3);
    for (int jj = 0; jj < Cuadro.rows; jj++) {
        uchar* renglon = Cuadro.ptr <uchar>(jj);
        for (int ii = 0; ii < (Cuadro.cols * Cuadro.channels()); ii+= Cuadro.channels()) {
            *(renglon + ii) = 255;
            *(renglon + ii+1) = 255;
            *(renglon + ii+2) = 255;
        }
    }

    cv::namedWindow("Cuadro", WINDOW_NORMAL);
    cv::imshow("Cuadro", Cuadro);

    cv::namedWindow("Original", WINDOW_NORMAL);
    cv::imshow("Original", Original);
    
    cv::namedWindow("Color", WINDOW_NORMAL);
    cv::imshow("Color", Grises);
    setMouseCallback("Original", CallBackFunc, NULL);
    setMouseCallback("Cuadro", CallBackFunc2, NULL);
    createTrackbar("Dis", "Original", &dis, 255 , Euclideana, &dis);

    
    printf("Realiza dos click para marcar la región en donde selecionara los puntos\n");
    
    while(true){
        
        if ( bandera =(char)cv::waitKey(0) == 'c')
            bandera = 1;

        if( bandera || ((cont-2)==25)){
            //if((char)cv::waitKey() == 'c' && cont>=2){
            //printf("Empieza\n");
                
            cv::imshow("Cuadro", Cuadro);
            printf("\nSeleccionó %d puntos\n", cont-2);
                mean(Matrix, cont-2, Y);
                printf("\nMedia de colores: \n%lf,%lf,%lf\n",Y[0],Y[1],Y[2]);
                printf("Haga click derecho para guardar\n");
                cont = 0;
                dis = 0;
                bandera = 0;
                colores = 0;
                
            //}((cont-2)==25) || (char)cv::waitKey(0) == 'c'
        }
    }

}

void MainWindow::on_cubicoBut_clicked()
{

    if(!existe_img)
    {
        QMessageBox::critical(this,"Error","Debes cargar una imagen");
        return;   
    }

    limitC=50;
    limitAnt=0;
    uno=0, dos=100;
    infeior_alpha = 20;
    superior_alpha = 45;
    dis=0;
    cont = 0;
    colores = 0;
    bandera = 0;
    s.append("S.jpg");
    Original=img.clone();
    nCanales = Original.channels();
    nR = Original.rows;
    nC = Original.cols * nCanales;
    
    //cv::cvtColor(Original, intermedio, CV_BGR2GRAY);
    //cv::cvtColor(intermedio, Grises, CV_GRAY2BGR);
    cv::cvtColor(Original, intermedio, COLOR_BGR2GRAY);
    cv::cvtColor(intermedio, Grises, COLOR_GRAY2BGR);

    Respaldo = Original.clone();
    Guardar = Respaldo.clone();

    //Mat Cuadro(100, 1000, CV_8UC3);
    for (int jj = 0; jj < Cuadro.rows; jj++) {
        uchar* renglon = Cuadro.ptr <uchar>(jj);
        for (int ii = 0; ii < (Cuadro.cols * Cuadro.channels()); ii+= Cuadro.channels()) {
            *(renglon + ii) = 255;
            *(renglon + ii+1) = 255;
            *(renglon + ii+2) = 255;
        }
    }

    cv::namedWindow("Cuadro", WINDOW_NORMAL);
    cv::imshow("Cuadro", Cuadro);

    cv::namedWindow("Original", WINDOW_NORMAL);
    cv::imshow("Original", Original);
    
    cv::namedWindow("Color", WINDOW_NORMAL);
    cv::imshow("Color", Grises);
    setMouseCallback("Original", CallBackFunc, NULL);
    setMouseCallback("Cuadro", CallBackFunc2, NULL);
    createTrackbar("Dis", "Original", &dis, 255 , Cubo, &dis);

    
    printf("Realiza dos click para marcar la región en donde selecionara los puntos\n");
    
    while(true){
        
        if ( bandera =(char)cv::waitKey(0) == 'c')
            bandera = 1;

        if( bandera || ((cont-2)==25)){
            //if((char)cv::waitKey() == 'c' && cont>=2){
            //printf("Empieza\n");
                
            cv::imshow("Cuadro", Cuadro);
            printf("\nSeleccionó %d puntos\n", cont-2);
                mean(Matrix, cont-2, Y);
                printf("\nMedia de colores: \n%lf,%lf,%lf\n",Y[0],Y[1],Y[2]);
                printf("Haga click derecho para guardar\n");
                cont = 0;
                dis = 0;
                bandera = 0;
                colores = 0;
                
            //}((cont-2)==25) || (char)cv::waitKey(0) == 'c'
        }
    }
}

void MainWindow::on_circularBut_clicked()
{

    if(!existe_img)
    {
        QMessageBox::critical(this,"Error","Debes cargar una imagen");
        return;   
    }
    limitC=50;
    limitAnt=0;
    uno=0, dos=100;
    infeior_alpha = 20;
    superior_alpha = 45;
    dis=0;
    cont = 0;
    colores = 0;
    bandera = 0;
    s.append("S.jpg");
    Original=img.clone();
    nCanales = Original.channels();
    nR = Original.rows;
    nC = Original.cols * nCanales;
    
    //cv::cvtColor(Original, intermedio, CV_BGR2GRAY);
    //cv::cvtColor(intermedio, Grises, CV_GRAY2BGR);
    cv::cvtColor(Original, intermedio, COLOR_BGR2GRAY);
    cv::cvtColor(intermedio, Grises, COLOR_GRAY2BGR);

    Respaldo = Original.clone();
    Guardar = Respaldo.clone();

    //Mat Cuadro(100, 1000, CV_8UC3);
    for (int jj = 0; jj < Cuadro.rows; jj++) {
        uchar* renglon = Cuadro.ptr <uchar>(jj);
        for (int ii = 0; ii < (Cuadro.cols * Cuadro.channels()); ii+= Cuadro.channels()) {
            *(renglon + ii) = 255;
            *(renglon + ii+1) = 255;
            *(renglon + ii+2) = 255;
        }
    }

    cv::namedWindow("Cuadro", WINDOW_NORMAL);
    cv::imshow("Cuadro", Cuadro);

    cv::namedWindow("Original", WINDOW_NORMAL);
    cv::imshow("Original", Original);
    
    cv::namedWindow("Color", WINDOW_NORMAL);
    cv::imshow("Color", Grises);
    setMouseCallback("Original", CallBackFunc, NULL);
    setMouseCallback("Cuadro", CallBackFunc2, NULL);
    createTrackbar("Dis", "Original", &dis, 255 , DMah, &dis);

    
    printf("Realiza dos click para marcar la región en donde selecionara los puntos\n");
    
    while(true){
        
        if ( bandera =(char)cv::waitKey(0) == 'c')
            bandera = 1;

        if( bandera || ((cont-2)==25)){
            
            cv::imshow("Cuadro", Cuadro);
            printf("\nSeleccionó %d puntos\n", cont-2);
                mean(Matrix, cont-2, Y);
                printf("\nMedia de colores: \n%lf,%lf,%lf\n",Y[0],Y[1],Y[2]);
                printf("Haga click derecho para guardar\n");
                covarianza(Matrix, cont-2, cov);
                inverse(cov, inv);
                cont = 0;
                dis = 0;
                bandera = 0;
                colores = 0;
        }
        //}
    }
}

void MainWindow::on_cromaticoBut_clicked()
{

    if(!existe_img)
    {
        QMessageBox::critical(this,"Error","Debes cargar una imagen");
        return;   
    }


    limitC=50;
    limitAnt=0;
    uno=0, dos=100;
    infeior_alpha = 20;
    superior_alpha = 45;
    dis=0;
    cont = 0;
    colores = 0;
    bandera = 0;
    s.append("S.jpg");
    Original=img.clone();
    nCanales = Original.channels();
    nR = Original.rows;
    nC = Original.cols * nCanales;
    
    //cv::cvtColor(Original, intermedio, CV_BGR2GRAY);
    //cv::cvtColor(intermedio, Grises, CV_GRAY2BGR);
    cv::cvtColor(Original, intermedio, COLOR_BGR2GRAY);
    cv::cvtColor(intermedio, Grises, COLOR_GRAY2BGR);

    Respaldo = Original.clone();
    Guardar = Respaldo.clone();

    //Mat Cuadro(100, 1000, CV_8UC3);
    for (int jj = 0; jj < Cuadro.rows; jj++) {
        uchar* renglon = Cuadro.ptr <uchar>(jj);
        for (int ii = 0; ii < (Cuadro.cols * Cuadro.channels()); ii+= Cuadro.channels()) {
            *(renglon + ii) = 255;
            *(renglon + ii+1) = 255;
            *(renglon + ii+2) = 255;
        }
    }

    cv::namedWindow("Cuadro", WINDOW_NORMAL);
    cv::imshow("Cuadro", Cuadro);

    cv::namedWindow("Original", WINDOW_NORMAL);
    cv::imshow("Original", Original);
    
    cv::namedWindow("Color", WINDOW_NORMAL);
    cv::imshow("Color", Grises);
    setMouseCallback("Original", CallBackFunc, NULL);
    setMouseCallback("Cuadro", CallBackFunc2, NULL);
    createTrackbar("Dis", "Original", &dis, 255 , Cubo, &dis);

    
    printf("Realiza dos click para marcar la región en donde selecionara los puntos\n");
    
    while(true){
        
        if ( bandera =(char)cv::waitKey(0) == 'c')
            bandera = 1;

        if( bandera || ((cont-2)==25)){
            //if((char)cv::waitKey() == 'c' && cont>=2){
            //printf("Empieza\n");
                
            cv::imshow("Cuadro", Cuadro);
            printf("\nSeleccionó %d puntos\n", cont-2);
                mean(Matrix, cont-2, Y);
                printf("\nMedia de colores: \n%lf,%lf,%lf\n",Y[0],Y[1],Y[2]);
                printf("Haga click derecho para guardar\n");
                cont = 0;
                dis = 0;
                bandera = 0;
                colores = 0;
                
            //}((cont-2)==25) || (char)cv::waitKey(0) == 'c'
        }
    }
}

void MainWindow::on_open_clicked()
{
    
}

void MainWindow::on_umbralSlider_sliderMoved(int position)
{
    
}
