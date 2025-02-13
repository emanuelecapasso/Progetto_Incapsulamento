#ifndef FUNZIONI_H
#define FUNZIONI_H
#include <string>
using namespace std;


//Struct dell'header IP contenente tutti i suoi campi
struct IpHeader{
    string version;
    string HLEN;
    string TOS;
    string totalLength;
    string identification;
    string flag;
    string fragmentOffset;
    string TTL;
    string protocol;
    string headerChecksum;
    string sourceAddress;
    string destinationAddress;
    string data;
};


//Struct dell'header Ethernet contenente tutti i suoi campi
struct ethernetHeader{
    string preamble;
    string SFD;
    string destinationAddress;
    string sourceAddress;
    string type;
    IpHeader ipHeader;              //Campo dati
    string FCS;
};


string leggiDaFile();
void scriviSuFile(string frame);
string convertiInBinario(string testo);
void creaDatagram(IpHeader &header);
void creaFrame(ethernetHeader &header, IpHeader headerIP);
string datagramInBinario(IpHeader &header);
string frameInBinario(ethernetHeader &header);
string calcolaCRC(string frameBinario);
string calcolaChecksumIp(IpHeader &header);


#endif