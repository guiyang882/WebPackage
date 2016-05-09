#include "captureform.h"
#include "ui_captureform.h"

CaptureForm::CaptureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureForm)
{
    ui->setupUi(this);
}

CaptureForm::~CaptureForm()
{
    delete ui;
}

void CaptureForm::on_comboBox_interface_currentIndexChanged(int index)
{

}

void CaptureForm::on_comboBox_protocal_currentIndexChanged(int index)
{

}

void CaptureForm::on_pushButton_start_clicked()
{

}

void CaptureForm::on_pushButton_finish_clicked()
{

}

void CaptureForm::on_pushButton_save_clicked()
{

}
