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


using namespace std;
typedef std::vector<double> Wektor;


class Neuron
{

    public:
        Wektor wagi;
        Wektor stareWagi;   // potrzebne do propagacji wstecznej
        double wyjscie;
        bool czyJestBias;
        double wartoscBiasu;
        double blad;
        double wyjscieSumatora; // potrzebne bo z niego obliczana pochodna funkcji aktywacji

        void obliczWyjscie(Wektor wejscia);
        double funkcjaAktywacji(double x);
        double pochodnaFunkcjiAktywacji(double x);
        void setWyjscie(double x); // liczy z sumy wartosc funkcji aktywacji i zapisuje do wyjscie
        
        Neuron(int iloscWejsc, bool bias=false);


        virtual ~Neuron();

    protected:

    private:
};

#endif /* NEURON_H */

