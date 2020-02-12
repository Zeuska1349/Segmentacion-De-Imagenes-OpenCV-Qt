/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir_imagen;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cuadradoBut;
    QPushButton *cubicoBut;
    QPushButton *circularBut;
    QPushButton *cromaticoBut;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QSlider *umbralSlider;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *AbrirBut;
    QSpacerItem *horizontalSpacer_7;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *imgContainers;
    QLabel *imgResultado;
    QLabel *imgOriginal;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(796, 667);
        actionAbrir_imagen = new QAction(MainWindow);
        actionAbrir_imagen->setObjectName(QStringLiteral("actionAbrir_imagen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 450, 771, 91));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        cuadradoBut = new QPushButton(gridLayoutWidget);
        cuadradoBut->setObjectName(QStringLiteral("cuadradoBut"));

        horizontalLayout_4->addWidget(cuadradoBut);

        cubicoBut = new QPushButton(gridLayoutWidget);
        cubicoBut->setObjectName(QStringLiteral("cubicoBut"));

        horizontalLayout_4->addWidget(cubicoBut);

        circularBut = new QPushButton(gridLayoutWidget);
        circularBut->setObjectName(QStringLiteral("circularBut"));

        horizontalLayout_4->addWidget(circularBut);

        cromaticoBut = new QPushButton(gridLayoutWidget);
        cromaticoBut->setObjectName(QStringLiteral("cromaticoBut"));

        horizontalLayout_4->addWidget(cromaticoBut);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 570, 771, 41));
       

        horizontalLayoutWidget_6 = new QWidget(centralwidget);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(9, 420, 771, 27));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        AbrirBut = new QPushButton(horizontalLayoutWidget_6);
        AbrirBut->setObjectName(QStringLiteral("AbrirBut"));

        horizontalLayout_6->addWidget(AbrirBut);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 771, 391));
        imgContainers = new QHBoxLayout(horizontalLayoutWidget);
        imgContainers->setObjectName(QStringLiteral("imgContainers"));
        imgContainers->setContentsMargins(0, 0, 0, 0);
        imgResultado = new QLabel(horizontalLayoutWidget);
        imgResultado->setObjectName(QStringLiteral("imgResultado"));

        imgContainers->addWidget(imgResultado);

        imgOriginal = new QLabel(horizontalLayoutWidget);
        imgOriginal->setObjectName(QStringLiteral("imgOriginal"));

        imgContainers->addWidget(imgOriginal);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 796, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAbrir_imagen->setText(QApplication::translate("MainWindow", "Abrir imagen", 0));
        label_3->setText(QApplication::translate("MainWindow", "Metodo", 0));
        cuadradoBut->setText(QApplication::translate("MainWindow", "Cuadrado", 0));
        cubicoBut->setText(QApplication::translate("MainWindow", "Cubico", 0));
        circularBut->setText(QApplication::translate("MainWindow", "Mahalanobis", 0));
        cromaticoBut->setText(QApplication::translate("MainWindow", "Cromatico", 0));
        //label_4->setText(QApplication::translate("MainWindow", "Umbral", 0));
        AbrirBut->setText(QApplication::translate("MainWindow", "Abrir", 0));
        imgResultado->setText(QApplication::translate("MainWindow", "Para utilizar los metodos\nde segmentacion\n seguir los siguientes pasos:\n1.- Abrir imagen a segmentar\n2.- Seleccionar el modo de segmentado\nApareceran 3 nuevas ventanas:\nEn la ventana Original\nse seleccionan los pixeles\npara la segmentacion\nuna vez seleccionados presione 'c' para\nrealizar la segmentacion.\nSi desea cambiar algun color de la seleccion\nsolo seleccionar el cuadro en la ventana Cuadro\ny asi se removerá el color.\nEl resultado se muestra en la ventana Color\nPuede guardar la imagen despues\n de haber sido segmentada oprimiedno\n click derecho, se guardara\n con el nombre segmentado.jpg\n", 0));
        imgOriginal->setText(QApplication::translate("MainWindow", "Abrir Imagen", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
