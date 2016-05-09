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

private slots:
    void on_comboBox_interface_currentIndexChanged(int index);

    void on_comboBox_protocal_currentIndexChanged(int index);

    void on_pushButton_start_clicked();

    void on_pushButton_finish_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::CaptureForm *ui;
};

#endif // CAPTUREFORM_H
