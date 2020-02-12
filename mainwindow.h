#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_AbrirBut_clicked();

    void on_cuadradoBut_clicked();

    void on_cubicoBut_clicked();

    void on_circularBut_clicked();

    void on_cromaticoBut_clicked();

    void on_umbralSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
