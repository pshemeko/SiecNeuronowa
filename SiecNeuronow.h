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

int ILOSCWEJSC = 4;
bool CZY_BIAS = false;
int ETA = 0.6;


using namespace std;

//dane wejscieowe
vector<vector<int> > daneWejsciowe;
vector<vector<int>> daneWyjsciowe;// = {(0,0,0,1),(0,0,1,0),(0,1,0,0,), (1,0,0,0)};

// iloscNeuronowNaWarstwe- ile mamy warste i neuronow w warstwie kazdy element vektora pokazuje ile jest neuronow w danej warstwie tj
// iloscNeuronowNaWarstwe[1] = 3  - mowi ze w warstwie 1 mamy 3 neurony
//vector<int> iloscNeuronowNaWarstwe = {4,2,4};

class SiecNeuronow
{
   //SiecNeuronow:: vector<vector<Neuron> > siec
    vector<Neuron*> wejscie; // warstwa wejsciowa kazdy neuron ma tylko jedno wejscie i jedna wage
    vector<vector<Neuron*> > siecNeuronow; // wartwa ukryta oraz wyjsciowa
    vector<vector<double> > siecWyjsc;
    
    vector<int> iloscNeuronowNaWarstwe;// = {4,2,4} w konstruktorze inicjuje
    
public:
    void obliczanieWag(vector<int> danaWej);//); //najpierw trzeba obliczyc wagi z danej 
    void obliczanieBledow(vector<int> danaWyj);
    void ZmianaWagSieci(vector<int> daneWej); // przekaz kolejna dana wejsciowa do uczenia sieci
    
    SiecNeuronow(int iloscWarstw, vector<int> iloscNeuronowNaWarstwe2 = {4,2,4});//, int neuronowNaKazdejWarstwieUkrytej);

        virtual ~SiecNeuronow();

        void temp(); // tymczasowa by zainicjoac wektory wejscia i wyjscia potem zmienic na odczyt z pliku
    protected:

    private:
};
#endif /* SIECNEURONOW_H */

