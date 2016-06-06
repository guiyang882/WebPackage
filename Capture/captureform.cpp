#include "captureform.h"
#include "ui_captureform.h"

CaptureForm::CaptureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureForm)
{
    p_alldevs = NULL;
    p_curSniffDev = NULL;
    m_curProtocal = "HTTP";
    ui->setupUi(this);
    getGlobalInterfaceDevs();
    p_worker = NULL;
    p_worker = new Worker(this);
}

CaptureForm::~CaptureForm() {
    if(p_alldevs)
        pcap_freealldevs(p_alldevs);
    if(p_worker) {
        p_worker->deleteLater();
        delete p_worker;
    }
    delete ui;
}

void CaptureForm::on_comboBox_interface_currentIndexChanged(int) {
    m_curSniffDev = ui->comboBox_interface->currentText().toStdString();
}

void CaptureForm::on_comboBox_protocal_currentIndexChanged(int) {
    m_curProtocal = ui->comboBox_protocal->currentText().toStdString();
}

void CaptureForm::on_pushButton_start_clicked() {
    if(ui->pushButton_start->text() == "Start") {
        QString fileterStr = ui->lineEdit_filter->text();
        p_curSniffDev = pcap_open_live(m_curSniffDev.c_str(),200, 0, 300, errbuf);
        int status = -1;
        if(p_curSniffDev == NULL) {
            cerr << "Couldn't open device " << m_curSniffDev << endl;
            QMessageBox::information(this, tr("Valid Device"), tr(errbuf), QMessageBox::Yes, QMessageBox::Yes);
        } else {
            struct bpf_program filter;
            if(fileterStr.isEmpty() == false) {
                status = pcap_compile(p_curSniffDev, &filter, fileterStr.toStdString().c_str(), 1, 0);
                if(status == -1) {
                    cerr << "pcap_compile: " << pcap_geterr(p_curSniffDev) << endl;
                }
                status = pcap_setfilter(p_curSniffDev, &filter);
                if(status == -1) {
                    cerr << "pcap_setfilter: " << pcap_geterr(p_curSniffDev) << endl;
                }
            }
            status = pcap_datalink(p_curSniffDev);
            if(status == -1) {
                cerr << "pcap_datalink: " << pcap_geterr(p_curSniffDev) << endl;
            }
        }

        p_worker->set_capture_device(p_curSniffDev);
        p_worker->start();
        ui->pushButton_start->setText(tr("Stop"));

    } else if(ui->pushButton_start->text() == "Stop") {
        p_worker->terminate_process();
        p_worker->quit();
    }
}

void CaptureForm::getGlobalInterfaceDevs() {
    if(p_alldevs) {
        pcap_freealldevs(p_alldevs);
        p_alldevs = NULL;
    }

    m_str2interface.clear();
    pcap_if_t *b;
    if(pcap_findalldevs(&p_alldevs, errbuf) == -1) {
        cout << "Error in pcap_findalldevs " << errbuf << endl;
    } else {
        for(b = p_alldevs;b != NULL;b = b->next) {
            if(b->name && b->addresses) {
                m_str2interface[string(b->name)] = b;
                if(b->description)
                    cout << b->description << endl;
            }
        }
    }
    updateInterface2UI();
}

void CaptureForm::updateInterface2UI() {
    ui->comboBox_interface->clear();
    for(auto it=m_str2interface.begin(); it!=m_str2interface.end(); it++) {
        ui->comboBox_interface->addItem(QString(it->first.c_str()));
    }
    ui->comboBox_interface->setCurrentIndex(0);
}
