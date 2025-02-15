#include "Funzioni.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <cstdlib>
using namespace std;


//Leggo il messaggio dal file Messaggio.txt
string leggiDaFile(){
    ifstream fin("Messaggio.txt");
    string testo;

    if(!fin){
        cout<<"Errore nell'apertura del file di lettura"<<endl;
        exit(1);
    }else{
        getline(fin, testo);
        fin.close();
    }
    return testo;
}


//Scrivo il frame finale sul file Frame.txt
void scriviSuFile(string frame){
    ofstream fout("Frame.txt");
    if(!fout){
        cout<<"Errore nell'apertura del file di scrittura"<<endl;
        exit(1);
    }else{
        fout<<frame<<endl;
        fout.close();
    }
}


string convertiInBinario(string testo){
    string numeroBinario = "";
    for(char c : testo){
        numeroBinario += bitset<8>(c).to_string();          //Sfrutto bitset per convertire in binario il messaggio
    }
    return numeroBinario;
}


void creaDatagram(IpHeader &header){
    header.version = "0100";                                                 //Versione del protocollo IP
    header.HLEN = "0101";                                                    //Lunghezza dell'header in parole
    header.TOS = "01100110";                                                 //Type of service
    header.totalLength = "0000000000111100";                                 //Lunghezza totale del datagramma
    header.identification = "1101010011110001";                              //Numero di identificazione
    header.flag = "010";
    header.fragmentOffset = "0000000000000";
    header.TTL = "01000000";                                                 //Time to live
    header.protocol = "00000110";                                            //Protocollo del livello superiore
    header.headerChecksum = "0000000000000000";                              //Checksum impostato a tutti 0
    header.sourceAddress = "11000000101010000000000100001010";               //Indirizzo IP del mittente
    header.destinationAddress = "00001000000010000000000000001000";          //Indirizzo IP del destinatario
    header.data = convertiInBinario(leggiDaFile());                          //Contenuto del messaggio in binario
    header.headerChecksum = calcolaChecksumIp(header);
}


void creaFrame(ethernetHeader &header, IpHeader headerIP){
    header.preamble = "10101010101010101010101010101010101010101010101010101010";
    header.SFD = "11010101";
    header.destinationAddress = "101011111010111110101111101011111010111110101111";
    header.sourceAddress = "101011001010111110101101101011001010011010101110";
    header.type = "1000000000000000";
    header.ipHeader = headerIP;
    header.FCS = calcolaCRC(frameInBinario(header));                         
}


string datagramInBinario(IpHeader &header){
    return header.version +
           header.HLEN +
           header.TOS +
           header.totalLength +
           header.identification +
           header.flag +
           header.fragmentOffset +
           header.TTL +
           header.protocol +
           header.headerChecksum +
           header.sourceAddress +
           header.destinationAddress +
           header.data;
}


string frameInBinario(ethernetHeader &header){
    return header.preamble +
           header.SFD +
           header.destinationAddress +
           header.sourceAddress +
           header.type +
           datagramInBinario(header.ipHeader) +
           header.FCS;
}


//Calcolo del CRC (riscritto, il codice fornito dal professore dava problemi)
string calcolaCRC(string frameBinario){
    unsigned int crc = 0xFFFFFFFF;
    for (char bit : frameBinario) {
        crc ^= (bit == '1' ? 1 : 0);
        for (int i = 0; i < 8; i++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    crc = ~crc;
    return bitset<32>(crc).to_string();
}


//Calcola l'IP checksum(riscritto, il codice del professore dava problemi)
string calcolaChecksumIp(IpHeader &header){
    string headerBits = header.version + header.HLEN + header.TOS +
                        header.totalLength + header.identification +
                        header.flag + header.fragmentOffset +
                        header.TTL + header.protocol +
                        header.sourceAddress + header.destinationAddress;

    unsigned int somma = 0;
    for (size_t i = 0; i < headerBits.length(); i += 16) {
        unsigned int blocco = stoi(headerBits.substr(i, 16), nullptr, 2);
        somma += blocco;
    }

    while (somma > 0xFFFF) {
        somma = (somma & 0xFFFF) + (somma >> 16);
    }

    somma = ~somma & 0xFFFF;
    return bitset<16>(somma).to_string();
}