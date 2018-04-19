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

using namespace std;

class Dane {
public:
    Dane();
    //Dane(const Dane& orig);
    vector<int> pobierzWejscie(int x);
    vector<int> pobierzWyjscie(int x);
    
    virtual ~Dane();
private:

};

#endif /* DANE_H */

