/*

        PROGETTO INCAPSULAMENTO
        
        Sistemi e reti
        Emanuele Capasso
*/


#include <bitset>
#include <fstream>
#include <iostream>
#include "Funzioni.h"
using namespace std;


int main(){
    string messaggio = leggiDaFile();                                                       //Leggo il messaggio da file
    cout<<"Messaggio letto: "<<messaggio<<endl;

    messaggio = convertiInBinario(messaggio);                                               //Converto il messaggio letto in binario
    cout<<"Messaggio letto tradotto in binario: "<<messaggio<<endl;

    IpHeader header;
    creaDatagram(header);                                                                   //Crea l'header IP

    ethernetHeader frameHeader;
    creaFrame(frameHeader, header);                                                         //Creazione del frame Ethernet

    string frameBinario = frameInBinario(frameHeader);
    scriviSuFile(frameBinario);                                                             //Scrivo il messaggio finale sul file Frame.txt

    cout<<"Frame scritto correttamente sul file Frame.txt"<<endl;

    return 0;
}