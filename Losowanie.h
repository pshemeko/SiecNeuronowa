/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Losowanie.h
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:16
 */

#ifndef LOSOWANIE_H
#define LOSOWANIE_H

#include <random>

using namespace std;
class Losowanie
{
    uniform_real_distribution<> dist;
    mt19937 rng;
public:
    float losuj();

    Losowanie(); //podac -0.5, 0.5
        virtual ~Losowanie();
    static Losowanie& get();

};


#endif /* LOSOWANIE_H */

