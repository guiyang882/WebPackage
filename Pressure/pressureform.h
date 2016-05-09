#ifndef PRESSUREFORM_H
#define PRESSUREFORM_H

#include <QWidget>

namespace Ui {
class PressureForm;
}

class PressureForm : public QWidget
{
    Q_OBJECT

public:
    explicit PressureForm(QWidget *parent = 0);
    ~PressureForm();

private:
    Ui::PressureForm *ui;
};

#endif // PRESSUREFORM_H
