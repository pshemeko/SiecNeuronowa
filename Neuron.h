/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Neuron.h
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:14
 */

#ifndef NEURON_H
#define NEURON_H


#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>


using namespace std;
typedef std::vector<double> Wektor;


class Neuron
{

    public:
        Wektor wagi;
        Wektor stareWagi;   // potrzebne do propagacji wstecznej
        double wyjscie;
       // Wektor wejsciaNeuronu; //to sa wejscia czyli wyjscia z poprzednich warstw
        bool czyJestBias;
        double wartoscBiasu;    // wywalic jako stala statyczna poza klase
        double blad;
        double wyjscieSumatora; // potrzebne bo z niego obliczana pochodna funkcji aktywacji

        void obliczWyjscieSumatora(Wektor wejscia);
        double funkcjaAktywacji(double x);
        double pochodnaFunkcjiAktywacji(double x);
        void setWyjscie(double x); // liczy z sumy wartosc funkcji aktywacji i zapisuje do wyjscie
        void przepiszDoStarejWagi();
        
        Neuron(int iloscWejsc,  bool bias=false);

        string wypisz();

        virtual ~Neuron();

    protected:

    private:
};

#endif /* NEURON_H */

