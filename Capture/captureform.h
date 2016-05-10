#ifndef CAPTUREFORM_H
#define CAPTUREFORM_H

#include <iostream>
#include <map>

#include <QWidget>
#include <QMessageBox>

#include <pcap/pcap.h>
#include <time.h>

using namespace std;

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
    void on_comboBox_interface_currentIndexChanged(int);
    void on_comboBox_protocal_currentIndexChanged(int);
    void on_pushButton_start_clicked();
    void on_pushButton_finish_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::CaptureForm *ui;

public:
    void getGlobalInterfaceDevs();
    void updateInterface2UI();

private:
    pcap_if_t* p_alldevs;
    map<string, pcap_if_t*> m_str2interface;
    char errbuf[PCAP_ERRBUF_SIZE];

private:
    pcap_t * p_curSniffDev;
    string m_curSniffDev;
    string m_curProtocal;
};

#endif // CAPTUREFORM_H
