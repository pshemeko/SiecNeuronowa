//
// Created by Przemo on 2018-05-16.
//

#ifndef KWIATKI_SIECNEURONOW_H
#define KWIATKI_SIECNEURONOW_H

//#include <windows.h> // dla funkcji sleep do testu
#include <vector>
#include <iostream>
#include <algorithm>
#include "Neuron.h"

static bool CZY_BIAS = true;
static bool CZY_Z_MOMENTEM = true;
//wspóczynniki
static double ETA = 0.1; // współczynnik nauki(0.6)
static double MI = 0.9; // potrzbne gdy licze z momentem (0.1)


using namespace std;

class SiecNeuronow {

public:
    vector<vector<Neuron*> > siecNeuronow;

    vector<int> iloscNeuronowNaWarstwe;  // = {4,2,4} w konstruktorze inicjuje

    SiecNeuronow(vector<int> iloscNeuronowNaWarstweDomyslna = {4,2,3});
    virtual ~SiecNeuronow() = default;

    double bladSieci();

    void obliczanieWyjsciaNeuronow(vector<double> danaWej);
    void obliczanieBledow(vector<double> danaWyj);
    void ZmianaWagSieci();

    void wypiszSiebie();
    void wypiszBledy();
    void wypiszRaz(vector<double> wyj);
    int testowanieSieci2(vector<double> wejscie, vector<double> wyjscie); // zwraca true jesli kwiatek sotal dobrze wykrytyile kwiatkow dbrze wykryto
};


#endif //KWIATKI_SIECNEURONOW_H
