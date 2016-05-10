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
}

CaptureForm::~CaptureForm() {
    if(p_alldevs)
        pcap_freealldevs(p_alldevs);
    delete ui;
}

void CaptureForm::on_comboBox_interface_currentIndexChanged(int) {
    m_curSniffDev = ui->comboBox_interface->currentText().toStdString();
}

void CaptureForm::on_comboBox_protocal_currentIndexChanged(int) {
    m_curProtocal = ui->comboBox_protocal->currentText().toStdString();
}

void CaptureForm::on_pushButton_start_clicked() {
    QString tmp = ui->lineEdit_filter->text();
    p_curSniffDev = pcap_open_live(m_curSniffDev.c_str(),65535, 1, 1000, errbuf);
    if(p_curSniffDev == NULL) {
        cerr << "Couldn't open device " << m_curSniffDev << endl;
        QMessageBox::information(this, tr("Valid Device"), tr(errbuf), QMessageBox::Yes, QMessageBox::Yes);
    } else {
        struct pcap_pkthdr packet;
        const u_char * pktStr = pcap_next(p_curSniffDev, &packet);
        if(pktStr == NULL) {
            cerr << "Did not capture a packet" << endl;
        } else {
            cout << "packed.len = " << packet.len << endl;
            cout << "Number of bytes = " << packet.caplen << endl;
            cout << "Recieved time = " << ctime((const time_t* )&packet.ts.tv_sec) << endl;
        }
    }
}

void CaptureForm::on_pushButton_finish_clicked() {

}

void CaptureForm::on_pushButton_save_clicked() {

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
            if(b->name) {
                m_str2interface[string(b->name)] = b;
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
