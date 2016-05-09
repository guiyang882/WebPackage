# webkiller
main to capture the packages from the some website, and test the website the load balancing !

## install libpcap
- download from http://www.tcpdump.org/
```bash
sudo apt-get install flex bison
mv libpcap-1.7.4.tar.gz /usr/local/src
sudo tar -zxvf libpcap-1.7.4.tar.gz
cd libpcap-1.7.4.tar.gz
sudo ./configure --prefix=/usr/local
sudo make -j4
sudo make install
```
- config qt project

```bash
#In webkiller.pro file add this
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lpcap
```
