/*
 * File:   Losowanie.h
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:16
 */

#ifndef KWIATKI_LOSOWANIE_H
#define KWIATKI_LOSOWANIE_H


#include <random>

using namespace std;
class Losowanie
{
    uniform_real_distribution<> dist;
    mt19937 rng;
    // do intow
    uniform_int_distribution<> liczbaNaturalna; // losujemy int od 0 do ileLiczb(z konstruktora)
    double min;
    double max;

public:
    double losujWagi();

    int losujInt();

    Losowanie(double dolnyZakres, double gornyZakres); //podac -0.5, 0.5 dla wag
    virtual ~Losowanie();
    //static Losowanie& get();

};


#endif //KWIATKI_LOSOWANIE_H
