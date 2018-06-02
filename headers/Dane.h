//
// Created by pobi on 5/14/18.
//

#ifndef KWIATKI_DANE_H
#define KWIATKI_DANE_H


#include <vector>

#include <random>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Losowanie.h"
#include "Neuron.h"

typedef std::vector< std::vector<double> > VEKTORDANYCH;

using namespace std;

class Dane {

public:
    VEKTORDANYCH dane; // 50 pierwsszegych kwiatkow, potem 50 druich potem trzecich

//    vector<double> maksima; // do normalizacji maksymalne wartosci danej zmiennej
//    vector<double> minima;  // do normalizacji
//    void normalizuj();

    Dane() = default;
    virtual ~Dane();
    void wczytaj_wzorzec(vector<Neuron*>  &wzorzec,char *nazwa);


//    vector<int> wylosujKolejnoscPobierania(int ileLiczb); // losuje kolejnosc liczb z przedz. [0, ileliczb) bez ileLiczb

    void wczytajPlik(string nazwaPliku = "iris.data", int ilosclinii = 150); // wczytuje dane z pliku iris.data do wektora par

    void wypiszWektor(VEKTORDANYCH wek);

};


#endif //KWIATKI_DANE_H
