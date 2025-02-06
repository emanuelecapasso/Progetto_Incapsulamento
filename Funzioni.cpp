#include "Funzioni.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <cstdlib>
using namespace std;


string leggiDaFile() {

  // Leggo dal file Messaggio.txt
  ifstream fin("Messaggio.txt");

  string testo;
  if (!fin) {
    cout << "Errore nell'apertura del file di lettura" << endl;
    exit(1);
  } else {
    getline(fin, testo);
    fin.close();
  }
  return testo;
}


void scriviSuFile(string frame) {

  // Scrivo sul file Frame.txt
  ofstream fout("Frame.txt");

  if (!fout) {
    cout << "Errore nell'apertura del file di scrittura" << endl;
    exit(1);
  } else {
    fout << frame << endl;
    fout.close();
  }
}


string convertiInBinario(string testo) {
  string numeroBinario = "";
  for (char c : testo) { // Scorro tutto il messaggio finchè riesco a leggerlo
    numeroBinario += bitset<8>(c).to_string() + ""; // Sfrutto bitset per convertire automaticamente un carattere in binario
  }
  return numeroBinario;
}


void creaDatagram(IpHeader &header) {
  header.versione = "4";   // Versione del protocollo IP
  header.HLEN = "5";       // Lunghezza dell'header in parole
  header.TOF = "00000000"; // Tutti i bit del type of service sono a 0
  header.totalLength = "0000000000011110"; // 30 byte perchè supponiamo un header di 20 byte e un messaggio letto di 10 byte
  header.identification = "12345"; // Numero di identificazione
  header.flag = "010";
  header.fragmentOffset = "000000000000";
  header.TTL = "64";              // Time to livee
  header.protocol = "00000110";   // Protocollo del livello superiore
  header.headerChecksum = "0000"; // Controllo degli errori
}