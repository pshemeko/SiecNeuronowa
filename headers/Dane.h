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
#include "SiecNeuronow.h"


using namespace std;

class Dane {

public:

    Dane() = default;
    virtual ~Dane();
    static void wczytaj_wzorzec(vector<Neuron*>  &wzorzec,char *nazwa);


    vector<int> wylosujKolejnoscPobierania(int ileLiczb); // losuje kolejnosc liczb z przedz. [0, ileliczb) bez ileLiczb


};


#endif //KWIATKI_DANE_H
