/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dane.h
 * Author: Przemo
 *
 * Created on 19 kwietnia 2018, 18:41
 */

#ifndef DANE_H
#define DANE_H
#include <vector>

#include <random>
#include <iostream>
#include <stdlib.h>
#include <fstream>

typedef std::vector<std::pair< std::vector<double>, std::vector<double> > > VEKTORPAR;

using namespace std;

class Dane {
public:
    uniform_real_distribution<> dist;
    uniform_int_distribution<> liczbaNaturalna;
    mt19937 gen;
    int ileLiczb;
    VEKTORPAR wektorPar;

    void wczytajPlik(string nazwaPliku = "iris.data", int ilosclinii = 150); // wczytuje dane z pliku iris.data do wektora par

    Dane(int ileLiczbLosowac);  // okresa ile z jakiego zakresu losujemy liczy ile ich bedzie
    //Dane(const Dane& orig);
    vector<double> pobierzWejscie(int x);
    vector<double> pobierzWyjscie(int x);

    vector<int> wylosujKolejnoscPobierania();
    virtual ~Dane();

    void menu() ;
    void menuTestowanie();
    void menuNaglowek();
    void normalizuj();
    void wypiszWektorPar();
};

#endif /* DANE_H */

