//Emanuele Capasso 4BI


#ifndef FUNZIONI_H
#define FUNZIONI_H
#include <string>  
using namespace std;  


//Struct dell'header IP contenente tutti i suoi campi
struct IpHeader{
    string version;
    string HLEN;
    string TOF;
    string totalLength;
    string identification;
    string flag;
    string fragmentOffset;
    string TTL;
    string protocol;
    string headerChecksum;
    string sourceAddress;
    string destinationAddress;
};


string leggiDaFile();
void scriviSuFile(string frame);
string convertiInBinario(string testo);
void creaDatagram(IpHeader &header);


#endif
