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
