/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SiecNeuronow.h
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:18
 */

#ifndef SIECNEURONOW_H
#define SIECNEURONOW_H

#include <vector>
#include "Neuron.h"
#include <iostream>
#include <windows.h> // dla funkcji sleep do testu

static int ILOSCWEJSC = 4;
static bool CZY_BIAS = true;
static double ETA = 0.6; // współczynnik nauki(0.6)
static bool ZMOMENTEM = true;
static double ALFHA = 0.1; // potrzbne gdy licze z momentem (0.1)

using namespace std;

class SiecNeuronow
{
public:
    vector<vector<int> > daneWejsciowe;     /// wywalic
    vector<vector<int>> daneWyjsciowe;      // = {(0,0,0,1),(0,0,1,0),(0,1,0,0,), (1,0,0,0)};

    vector<Neuron*> wejscie;                // warstwa wejsciowa kazdy neuron ma tylko jedno wejscie i jedna wage
    vector<vector<Neuron*> > siecNeuronow;  // wartwa ukryta oraz wyjsciowa
    vector<vector<double> > siecWyjsc;      // wyscia wszystkich neuronow tez z warstwy wejsciowej

    vector<int> iloscNeuronowNaWarstwe;     // = {4,2,4} w konstruktorze inicjuje
    
    void obliczanieWyjsciaNeuronow(vector<double> danaWej); //najpierw trzeba obliczyc wagi z danej
    void obliczanieBledow(vector<double> danaWyj);
    void ZmianaWagSieci(vector<double> daneWej);    // przekaz kolejna dana wejsciowa do uczenia sieci
    double bladCalkowity();     //zle
    double obliczBladDlaWzorca(vector<double> oczekiwanaWartosc);
    
    vector<int> losujeKolejnosc(int iloscWektorowZDanymi);

    void temp();    // tymczasowa by zainicjoac wektory wejscia i wyjscia potem zmienic na odczyt z pliku - chyba juz niepotrzebna

    void testowanieSieci(vector<double> wejscie, vector<double> wyjscie);

    void uczenie(int iloscEpok, double blad = 0.0);

    SiecNeuronow(vector<int> iloscNeuronowNaWarstwe2 = {4,2,4});

    virtual ~SiecNeuronow()=default;

};

#endif /* SIECNEURONOW_H */

