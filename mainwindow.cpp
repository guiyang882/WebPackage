#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    p_Capture = NULL;
    p_Pressure = NULL;
    p_CaptureLayout = NULL;
    p_PressureLayout = NULL;
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    if(p_CaptureLayout)
        delete p_CaptureLayout;
    if(p_PressureLayout)
        delete p_PressureLayout;
    if(p_Capture)
        delete p_Capture;
    if(p_Pressure)
        delete p_Pressure;
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index) {

    if(index == 0 && p_Capture == NULL) {
        p_CaptureLayout = new QGridLayout(ui->tab_Capture);
        p_Capture = new CaptureForm(ui->tab_Capture);
        p_CaptureLayout->addWidget(p_Capture);
        ui->tab_Capture->setLayout(p_CaptureLayout);
        p_Capture->setAutoFillBackground(true);
        p_Capture->show();
    }

    if(index == 1 && p_Pressure == NULL) {
        p_PressureLayout = new QGridLayout(ui->tab_Capture);
        p_Pressure = new PressureForm(ui->tab_Capture);
        p_PressureLayout->addWidget(p_Pressure);
        ui->tab_Pressure->setLayout(p_PressureLayout);
        p_Pressure->setAutoFillBackground(true);
        p_Pressure->show();
    }
}

void MainWindow::on_actionAbout_Developor_triggered() {
    QMessageBox::information(this, tr("Developers"),
                             tr("Liu Guiyang --- 2015E8018761022\nWang Zhaonan -- 201518013727087\nMa Lingwei -- 2015E8013761089"),
                             QMessageBox::Ok);
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QApplication::aboutQt();
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}
