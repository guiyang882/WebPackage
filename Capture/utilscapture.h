#ifndef UTILSCAPTURE_H
#define UTILSCAPTURE_H

#include <time.h>
#include <iostream>
#include <stdio.h>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#include <QThread>

#include "captureform.h"

using namespace std;

//链路层数据包格式
typedef struct {
    u_char DestMac[6];
    u_char SrcMac[6];
    u_char Etype[2];
}ETHHEADER;

//IP层数据包格式
typedef struct {
    int header_len:4;
    int version:4;
    u_char tos:8;
    int total_len:16;
    int ident:16;
    int flags:16;
    u_char ttl:8;
    u_char proto:8;
    int checksum:16;
    u_char sourceIP[4];
    u_char destIP[4];
}IPHEADER;

void pcap_handle(u_char* user,const struct pcap_pkthdr* header,const u_char* pkt_data);

class CaptureForm;
class Worker: public QThread {
public:
    Worker(CaptureForm* ui);
    ~Worker();
public:
    void set_capture_device(pcap_t* device);
    void terminate_process();

public:
    static string get_IPAddress(bpf_u_int32 ipaddress);
    static string get_NetMask(bpf_u_int32 ipmask);

public:
    void run();

private:
    pcap_t * m_curDev;
    CaptureForm *m_ui;
};

#endif // UTILSCAPTURE_H
