#include "utilscapture.h"
//协议映射表
string Proto[]={
    "Reserved","ICMP","IGMP","GGP","IP","ST","TCP"
};

Worker::Worker(CaptureForm* ui) {
    m_curDev = NULL;
    m_ui = ui;
}

Worker::~Worker() {
    if(m_curDev) {
        delete m_curDev;
    }
}

void Worker::set_capture_device(pcap_t *device) {
    m_curDev = device;
}

void Worker::run() {
    pcap_loop(m_curDev, -1, pcap_handle, NULL);
}

void Worker::terminate_process() {
    pcap_breakloop(m_curDev);
    pcap_close(m_curDev);
}

//回调函数
void pcap_handle(u_char* user,const struct pcap_pkthdr* header,const u_char* pkt_data) {
    ETHHEADER *eth_header=(ETHHEADER*)pkt_data;
    printf("---------------Begin Analysis-----------------\n");
    printf("----------------------------------------------\n");
    printf("Packet length: %d \n",header->len);
    //解析数据包IP头部
    if(header->len>=14){
        IPHEADER *ip_header=(IPHEADER*)(pkt_data+14);
        //解析协议类型
        char strType[100];
        if(ip_header->proto>7)
            strcpy(strType,"IP/UNKNWN");
        else
            strcpy(strType,Proto[ip_header->proto].c_str());

        printf("Source MAC : %02X-%02X-%02X-%02X-%02X-%02X==>",eth_header->SrcMac[0],eth_header->SrcMac[1],eth_header->SrcMac[2],eth_header->SrcMac[3],eth_header->SrcMac[4],eth_header->SrcMac[5]);
        printf("Dest   MAC : %02X-%02X-%02X-%02X-%02X-%02X\n",eth_header->DestMac[0],eth_header->DestMac[1],eth_header->DestMac[2],eth_header->DestMac[3],eth_header->DestMac[4],eth_header->DestMac[5]);

        printf("Source IP : %d.%d.%d.%d==>",ip_header->sourceIP[0],ip_header->sourceIP[1],ip_header->sourceIP[2],ip_header->sourceIP[3]);
        printf("Dest   IP : %d.%d.%d.%d\n",ip_header->destIP[0],ip_header->destIP[1],ip_header->destIP[2],ip_header->destIP[3]);

        printf("Protocol : %s\n",strType);

        //显示数据帧内容
        int i;
        for(i=0; i<(int)header->len; ++i)  {
            printf(" %02x", pkt_data[i]);
            if( (i + 1) % 16 == 0 )
                printf("\n");
        }
        printf("\n\n");
    }
}

string Worker::get_IPAddress(bpf_u_int32 ipaddress) {
    char ip[INET_ADDRSTRLEN];
    if(inet_ntop(AF_INET,&ipaddress,ip,sizeof(ip))==NULL)
        perror("inet_ntop error");
    printf("IP address: %s\n",ip);
    return string(ip);
}

string Worker::get_NetMask(bpf_u_int32 ipmask) {
    char mask[INET_ADDRSTRLEN];
    if(inet_ntop(AF_INET,&ipmask,mask,sizeof(mask))==NULL)
        perror("inet_ntop error");
    printf("Network Mask: %s\n",mask);
    return string(mask);
}
