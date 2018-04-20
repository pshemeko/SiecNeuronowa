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

using namespace std;
using namespace std;

class Dane {
public:
    uniform_real_distribution<> dist;
    uniform_int_distribution<> liczbaNaturalna;
    mt19937 gen;
    int ileLiczb;

    Dane(int ileLiczbLosowac);  // okresa ile z jakiego zakresu losujemy liczy ile ich bedzie
    //Dane(const Dane& orig);
    vector<double> pobierzWejscie(int x);
    vector<double> pobierzWyjscie(int x);

    vector<int> wylosujKolejnoscPobierania();
    virtual ~Dane();
private:

};

#endif /* DANE_H */

