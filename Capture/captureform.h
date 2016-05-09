#ifndef CAPTUREFORM_H
#define CAPTUREFORM_H

#include <QWidget>

namespace Ui {
class CaptureForm;
}

class CaptureForm : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureForm(QWidget *parent = 0);
    ~CaptureForm();

private:
    Ui::CaptureForm *ui;
};

#endif // CAPTUREFORM_H
