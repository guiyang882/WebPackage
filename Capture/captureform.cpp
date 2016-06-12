#include "captureform.h"
#include "ui_captureform.h"

CaptureForm::CaptureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureForm)
{
    ui->setupUi(this);
    ui->tableWidget_showPackages->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_showPackages->setColumnCount(8);
    ui->tableWidget_showPackages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_showPackages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_showPackages->setSortingEnabled(true);

    QPalette pal = ui->pushButton_start->palette();
    pal.setColor(QPalette::Button,Qt::green);
    ui->pushButton_start->setPalette(pal);
    ui->pushButton_start->setAutoFillBackground(true);
    ui->pushButton_start->setFlat(true);

    isCaputre = false;
    p_alldevs = NULL;
    p_curSniffDev = NULL;
    m_curProtocal = "HTTP";
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

void CaptureForm::setTableItem(QStringList data) {
    int cur_row = ui->tableWidget_showPackages->rowCount();
    int cur_col = 0;
    ui->tableWidget_showPackages->insertRow(cur_row);
    foreach (QString info, data) {
        cout << info.toStdString() << endl;
        QTableWidgetItem* item = new QTableWidgetItem(info, QTableWidgetItem::Type);
        ui->tableWidget_showPackages->setItem(cur_row, cur_col++,item);
    }
}

void CaptureForm::on_comboBox_interface_currentIndexChanged(int) {
    if(isCaputre == false) {
        m_curSniffDev = ui->comboBox_interface->currentText().toStdString();
    } else {
        QMessageBox::warning(this,"Warning",tr("You Should Stop Capture first !"),QMessageBox::Ok,QMessageBox::Ok);
    }
}

void CaptureForm::on_pushButton_start_clicked() {
    if(ui->pushButton_start->text() == "Start") {
        isCaputre = true;
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
            } else {
                cout << "fileter string is empty !" << endl;
            }
            status = pcap_datalink(p_curSniffDev);
            if(status == -1) {
                cerr << "pcap_datalink: " << pcap_geterr(p_curSniffDev) << endl;
            }
        }

        p_worker->set_capture_device(p_curSniffDev);
        p_worker->start();
        ui->pushButton_start->setText(tr("Stop"));
        QPalette pal = ui->pushButton_start->palette();
        pal.setColor(QPalette::Button,Qt::red);
        ui->pushButton_start->setPalette(pal);
        ui->pushButton_start->setAutoFillBackground(true);
        ui->pushButton_start->setFlat(true);

    } else if(ui->pushButton_start->text() == "Stop") {
        isCaputre = false;
        p_worker->terminate_process();
        p_worker->quit();
        ui->pushButton_start->setText(tr("Start"));
        QPalette pal = ui->pushButton_start->palette();
        pal.setColor(QPalette::Button,Qt::green);
        ui->pushButton_start->setPalette(pal);
        ui->pushButton_start->setAutoFillBackground(true);
        ui->pushButton_start->setFlat(true);
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

void CaptureForm::on_pushButton_clear_clicked() {
    if(isCaputre == false) {
        int row_num = ui->tableWidget_showPackages->rowCount();
        for (int index=0; index<row_num; index++) {
            ui->tableWidget_showPackages->removeRow(0);
        }
    } else {
        QMessageBox::warning(this,"Warning",tr("You Should Stop Capture first !"),QMessageBox::Ok,QMessageBox::Ok);
    }
}

void CaptureForm::on_pushButton_save_clicked() {
    if(isCaputre == false) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File")," ",tr("file (*.csv)"));
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            bool ret = file.open( QIODevice::Truncate | QIODevice::WriteOnly);
            if(!ret) {
                QMessageBox::warning(this,"Warning",tr("Open Save File Path Error !\nPlease Check Path Selected !"),
                                     QMessageBox::Ok,QMessageBox::Ok);
                return ;
            }

            QTextStream stream(&file);
            QString conTents;
            QHeaderView * header = ui->tableWidget_showPackages->horizontalHeader() ;
            if(header) {
                for(int i = 0; i < header->count(); i++) {
                    QTableWidgetItem *item = ui->tableWidget_showPackages->horizontalHeaderItem(i);
                    if(!item) {
                        continue;
                    }
                    conTents += item->text() + ",";
                }
                conTents += "\n";
            }

            for(int i = 0 ; i < ui->tableWidget_showPackages->rowCount(); i++) {
                for(int j = 0; j < ui->tableWidget_showPackages->columnCount(); j++) {
                    QTableWidgetItem* item = ui->tableWidget_showPackages->item(i, j);
                    if(!item)
                        continue;
                    QString str = item->text();
                    str.replace(","," ");
                    conTents += str + ",";
                }
                conTents += "\n";
            }
            stream << conTents;
            file.close();
        }
        QMessageBox::warning(this,"Information",tr("File Save OK !"),
                             QMessageBox::Ok,QMessageBox::Ok);

    } else {
        QMessageBox::warning(this,"Warning",tr("You Should Stop Capture first !"),QMessageBox::Ok,QMessageBox::Ok);
    }
}
