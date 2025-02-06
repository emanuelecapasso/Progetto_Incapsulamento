/*

PROGETTO INCAPSULAMENTO

Sistemi e reti
Emanuele Capasso 4BI
*/

#include <bitset>
#include <fstream>
#include <iostream>
#include "Funzioni.h"
using namespace std;


int main(){
  string messaggio = leggiDaFile();                                  //Leggo il messaggio da file
  cout<<"Messaggio letto: "<<messaggio<<endl;
  messaggio = convertiInBinario(messaggio);                          //Converto il messaggio letto in binario
  cout<<"Messaggio letto tradotto in binario: "<<messaggio<<endl;

  IpHeader header;
  creaDatagram(header);

  scriviSuFile(messaggio);                                           //Scrivo il messaggio finale, in binario, sul file
  cout<<"Messaggio scritto correttamente sul file"<<endl;

  return 0;
}
