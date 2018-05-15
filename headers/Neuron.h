//
// Created by Przemo on 2018-05-15.
//

#ifndef KWIATKI_NEURON_H
#define KWIATKI_NEURON_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>

#include "Neuron.h"
#include "Losowanie.h"

using namespace std;

typedef std::vector<double> Wektor;


class Neuron {

public:
    Wektor wagi;
    Wektor stareWagi;       // potrzebne do propagacji wstecznej
    double wyjscie;
    bool   czyJestBias;
    double wartoscBiasu;    // wywalic jako stala statyczna poza klase
    double blad;
    //double wyjscieSumatora; // potrzebne bo z niego obliczana pochodna funkcji aktywacji
    //double delta; // blad * pochodna funkcji aktywacji

    //void   ustawWyjscie(double x); // liczy z sumy wartosc funkcji aktywacji i zapisuje do wyjscie

    Neuron(int iloscWejsc, bool bias);
    virtual ~Neuron() = default;
};


#endif //KWIATKI_NEURON_H
