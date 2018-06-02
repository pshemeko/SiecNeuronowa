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
    //static double wartoscBiasu;    // wywalic jako stala statyczna poza klase
    //static bool   czyJestBias;

public:
    Wektor wagi;    // wspolrzedne neuronu

    Neuron( vector<int> zakres);
    Neuron( double x, double y); // DLA DANYCH Z PLIKU
    virtual ~Neuron() = default;
    Neuron() = default;
};


#endif //KWIATKI_NEURON_H
