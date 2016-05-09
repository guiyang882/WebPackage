#include "pressureform.h"
#include "ui_pressureform.h"

PressureForm::PressureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PressureForm)
{
    ui->setupUi(this);
}

PressureForm::~PressureForm()
{
    delete ui;
}
