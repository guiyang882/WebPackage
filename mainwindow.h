#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QGridLayout>
#include "Capture/captureform.h"
#include "Pressure/pressureform.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    CaptureForm *p_Capture;
    PressureForm *p_Pressure;

private:
    QGridLayout* p_CaptureLayout;
    QGridLayout* p_PressureLayout;
};

#endif // MAINWINDOW_H
